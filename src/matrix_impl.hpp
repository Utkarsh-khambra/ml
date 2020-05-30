#pragma once
#include "impl_details.hpp"
#include <cassert>
#include <compare>
#include <functional>
#include <gsl/gsl_errno.h>
#include <iostream>
/* #include <vector_impl.hpp> */
namespace gsl::details {
template <typename T, bool IsView>
requires(std::is_arithmetic_v<T>) class matrix_impl
    : private gsl_matrix_type<T> {
  using matrix_view_type = typename gsl_matrix_type<T>::view_type;
  using matrix_type = typename gsl_matrix_type<T>::type;
  using destructor = std::function<void(matrix_type *)>;
  using uptr = std::unique_ptr<matrix_type, destructor>;
  using base = gsl_matrix_type<T>;

public:
  template <std::input_iterator Itr, bool b = IsView,
            std::enable_if_t<!b, int> = 0>
  matrix_impl(Itr first, Itr last, size_t num_rows)
      : matrix(uptr(
            base::allocate(num_rows, std::distance(first, last) / num_rows),
            free)) {
    std::copy(first, last, matrix->data);
  }
  matrix_impl(std::initializer_list<T> values, size_t num_rows)
      : matrix_impl(values.begin(), values.end(), num_rows) {}

  matrix_impl(size_t row, size_t col)
      : base(), matrix(uptr(base::allocate(row, col), free)) {}

  matrix_impl(matrix_view_type view) : matrix_impl(view.matrix) {}

  matrix_impl(const matrix_impl &other) requires(!IsView)
      : matrix_impl(other.cbegin(), other.cend(), other.num_rows()) {
    /* std::cout << "Copy constructor\n"; */
  }

  matrix_impl(matrix_impl &&other) noexcept requires(!IsView)
      : matrix(std::move(other.matrix)) {}
  matrix_impl &operator=(matrix_impl other) requires(!IsView) {
    std::swap(matrix, other.matrix);
    return *this;
  }

  // Iterators

  // Operators

  T &operator()(size_t row, size_t col) noexcept {
    return *base::get_ptr(mat_ptr(), row, col);
  }
  const T &operator()(size_t row, size_t col) const noexcept {
    return *base::get_ptr(mat_ptr(), row, col);
  }
  matrix_impl operator+(const matrix_impl &other) const {
    assert(other.shape() == shape());
    auto ret(*this);
    auto result = base::add(ret.mat_ptr(), other.mat_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }
  matrix_impl operator+(const T value) const {
    auto ret(*this);
    auto result = base::add_constant(ret.mat_ptr(), value);
    if (result)
      handle_exception(result);
    return ret;
  }
  friend matrix_impl operator+(const T value, const matrix_impl &other) {
    return other + value;
  }
  matrix_impl operator-(const matrix_impl &other) const {
    assert(other.shape() == shape());
    auto ret(*this);
    auto result = base::sub(ret.mat_ptr(), other.mat_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }

  matrix_impl operator-(const T value) const {
    auto ret(*this);
    auto result = base::add_constant(ret.mat_ptr(), -value);
    if (result)
      handle_exception(result);
    return ret;
  }

  friend matrix_impl operator-(const T value, const matrix_impl &other) {
    return other - value;
  }

  matrix_impl operator*(const matrix_impl &other) const {
    assert(shape() == other.shape());
    auto ret(*this);
    auto result = base::mul(ret.mat_ptr(), other.mat_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }
  friend matrix_impl operator*(const T value, matrix_impl mat) {
    return mat * value;
  }
  matrix_impl operator*(const T value) const {
    auto ret(*this);
    auto result = base::scale(ret.mat_ptr(), value);
    if (result)
      handle_exception(result);
    return ret;
  }
  matrix_impl operator/(const matrix_impl &other) const {
    assert(shape() == other.shape());
    auto ret(*this);
    auto result = base::div(ret.mat_ptr(), other.mat_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }

  matrix_impl operator/(const T value) const {
    auto ret(*this);
    std::for_each(ret.begin(), ret.end(), [value](T &a) { a = a / value; });
    return ret;
  }

  // Functions
  auto get_matrix() const noexcept { return mat_ptr(); }
  auto get_matrix() noexcept { return mat_ptr(); }
  auto shape() const noexcept { return std::make_pair(num_rows(), num_cols()); }
  size_t num_rows() const noexcept { return mat_ptr()->size1; }
  size_t num_cols() const noexcept { return mat_ptr()->size2; }
  auto begin() noexcept { return mat_ptr()->data; }
  auto end() noexcept { return begin() + num_cols() * num_rows(); }
  auto begin() const noexcept { return mat_ptr()->data; }
  auto end() const noexcept { return begin() + num_cols() * num_rows(); }

  auto cbegin() const noexcept { return begin(); }
  auto cend() const noexcept { return end(); }
  matrix_impl transpose() const {
    matrix_impl ret(num_cols(), num_rows());
    int result;
    if (auto i = shape(); i.first == i.second) {
      ret = *this;
      result = base::transpose(ret.matrix.get());
      return ret;
    } else
      result = base::transpose_memcpy(ret.matrix.get(), matrix.get());
    if (result)
      handle_exception(result);
    return ret;
  }

  constexpr bool empty() const noexcept { return (mat_ptr() == nullptr); }
  constexpr T max() const noexcept { return base::max(mat_ptr()); }
  constexpr T min() const noexcept { return base::min(mat_ptr()); }
  constexpr auto minmax() const noexcept { return base::minmax(mat_ptr()); }
  constexpr auto min_index() const noexcept {
    return base::min_index(mat_ptr());
  }
  constexpr auto max_index() const noexcept {
    return base::max_index(mat_ptr());
  }
  constexpr auto minmax_index() const noexcept {
    return base::minmax_index(mat_ptr());
  }
  /* vector_impl<T, false> get_row(size_t row) const { */
  /*   vector_impl<T, false> ret(num_cols()); */
  /*   cpy_row(ret.get_vector(), matrix.get(), row); */
  /*   return ret; */
  /* } */

  /* vector_impl<T, false> get_col(size_t col) const { */
  /*   vector_impl<T, false> ret(num_rows()); */
  /*   cpy_col(ret.get_vector(), matrix.get(), col); */
  /*   return ret; */
  /* } */
  void print() const noexcept {
    size_t row = 0;
    auto ptr = mat_ptr();
    for (auto i = ptr->data; i != ptr->data + num_rows() * num_cols();
         i += num_cols()) {
      std::cout << "Row: " << row << " >> ";
      std::copy(i, i + num_cols(), std::ostream_iterator<T>(std::cout, " "));
      std::cout << '\n';
      ++row;
    }
  }

  void print(size_t rows) const noexcept {
    if (rows > num_rows())
      rows = num_rows();
    size_t row = 0;
    auto ptr = mat_ptr();
    for (auto i = ptr->data; i != ptr->data + rows * num_cols();
         i += num_cols()) {
      std::cout << "Row: " << row << " >> ";
      std::copy(i, i + num_cols(), std::ostream_iterator<T>(std::cout, " "));
      std::cout << '\n';
      ++row;
    }
  }

private:
  std::conditional_t<IsView, matrix_type, uptr> matrix;
  matrix_type *mat_ptr() noexcept {
    if constexpr (IsView)
      return &matrix.matrix;
    else
      return matrix.get();
  }
  const matrix_type *mat_ptr() const noexcept {
    if constexpr (IsView)
      return &matrix.matrix;
    else
      return matrix.get();
  }
  void handle_exception(int result) const { std::cout << result << '\n'; }
};
} // namespace gsl::details
