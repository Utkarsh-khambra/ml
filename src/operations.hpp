#pragma once
#include "matrix.hpp"
#include "vector.hpp"
#include <cmath>
#include <gsl/gsl_blas.h>
#include <numeric>
namespace gsl {
// Make it friend so that transpose can be evaluated lazily
template <typename T>
requires(std::is_floating_point_v<T>) matrix<T> cross(
    const gsl::matrix<T> &a, const gsl::matrix<T> &b) noexcept {
  auto ret(a);
  if constexpr (std::is_same_v<T, double>)
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, a.get_matrix(),
                   b.get_matrix(), 0, ret.get_matrix());
  if constexpr (std::is_same_v<T, float>)
    gsl_blas_sgemm(CblasNoTrans, CblasNoTrans, 1, a.get_matrix(),
                   b.get_matrix(), 0, ret.get_matrix());
  return ret;
}

template <typename T>
requires(std::is_arithmetic_v<T>) T
    dot(const vector<T> &a, const vector<T> &b) noexcept {
  T ret;
  if constexpr (std::is_same_v<T, double>)
    gsl_blas_ddot(a.get_vector(), b.get_vector(), &ret);
  else if constexpr (std::is_same_v<T, float>)
    gsl_blas_sdot(a.get_vector(), b.get_vector(), &ret);
  else
    return std::inner_product(a.cbegin(), a.cend(), b.cbegin(), (T)0);
  return ret;
}
template <typename T, typename R>
requires(std::conjunction_v<std::is_arithmetic<T>,
                            std::is_arithmetic<R>>) auto dot(const vector<T> &a,
                                                             const vector<R>
                                                                 &b) noexcept {
  return std::inner_product(a.cbegin(), a.cend(), b.cbegin(),
                            (std::common_type_t<T, R>)0);
}
template <typename T>
requires(std::is_arithmetic_v<T>) T norm2(const vector<T> &a) noexcept {
  T ret;
  if constexpr (std::is_same_v<T, double>)
    ret = gsl_blas_dnrm2(a.get_vector());
  else if constexpr (std::is_same_v<T, float>)
    ret = gsl_blas_snrm2(a.get_vector());
  else
    return std::sqrt(
        std::inner_product(a.cbegin(), a.cend(), a.cbegin(), (T)0));
  return ret;
}
template <typename T>
requires(std::is_arithmetic_v<T> &&std::is_floating_point_v<T>) auto dot(
    const matrix<T> &mat, const vector<T> &vec) {
  assert(mat.num_cols() == vec.length());
  vector<T> ret(mat.num_rows());
  if constexpr (std::is_same_v<T, float>)
    gsl_blas_sgemv(CblasNoTrans, 1, mat.get_matrix(), vec.get_vector(), 0,
                   ret.get_vector());
  if constexpr (std::is_same_v<T, double>)
    gsl_blas_dgemv(CblasNoTrans, 1, mat.get_matrix(), vec.get_vector(), 0,
                   ret.get_vector());
  else {
    return dot<T, T>(mat, vec);
  }
  return ret;
}

template <typename T, typename R>
requires(
    std::conjunction_v<std::is_arithmetic<T>,
                       std::is_arithmetic<R>>) auto dot(const matrix<T> &mat,
                                                        const vector<R> &vec) {
  vector<std::common_type_t<T, R>> ret(mat.num_rows());
  for (size_t i = 0; i < mat.num_rows(); ++i) {
    auto row = mat.get_row(i);
    ret[i] = std::inner_product(vec.begin(), vec.end(), row.begin(),
                                (std::common_type_t<T, R>)0);
  }
  return ret;
}
} // namespace gsl
