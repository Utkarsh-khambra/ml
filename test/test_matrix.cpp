#include "catch2/catch.hpp"
#include <execution>
#include <iostream>
#include <limits>
#include <matrix.hpp>
#include <random>
template <typename T>
requires(std::is_arithmetic_v<T>) auto generate_random_seq(size_t n,
                                                           int min = 10,
                                                           int max = 1000) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<T> ret(n);
  if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dis(min, max);
    std::for_each(std::execution::par_unseq, ret.begin(), ret.end(),
                  [&gen, &dis](T &a) { a = dis(gen); });
  } else {
    std::uniform_int_distribution<T> dis(min, max);
    std::for_each(std::execution::par_unseq, ret.begin(), ret.end(),
                  [&gen, &dis](T &a) { a = dis(gen); });
  }
  return ret;
}

TEST_CASE("Iterator constructor check") {
  std::vector<double> a{1, 4, 7, 8, 9, 6, 47, 23, 456};
  gsl::matrix<double> m(a.begin(), a.end(), 3);
  REQUIRE(m.num_rows() == 3);
  REQUIRE(m.num_cols() == 3);
  /*
   * 1 4 7
   * 8 9 6
   * 47 23 456
   * */
  // m.print();
}
TEST_CASE("Initailizer list check") {
  gsl::details::matrix_impl<double, false> m({1, 4, 7, 54, 63, 48, 123, 457, 4},
                                             3);
  REQUIRE(m.num_cols() == 3);
  REQUIRE(m.num_rows() == 3);
  /*
   * 1 4 7
   * 54 63 48
   * 123 457 4
   * */
  // m.print();
}
TEMPLATE_TEST_CASE("Copy Constructor", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  auto n(m);
  REQUIRE(std::equal(m.begin(), m.end(), n.begin()));
}
TEMPLATE_TEST_CASE("Move Constructor", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  auto n(m);
  auto p(std::move(m));
  REQUIRE(std::equal(n.begin(), n.end(), p.begin()));
  REQUIRE(m.empty());
}

TEMPLATE_TEST_CASE("Copy Assignment Operator", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  auto n = m;
  REQUIRE(std::equal(n.begin(), n.end(), m.begin()));
}
TEMPLATE_TEST_CASE("Move Assignment Operator", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  auto n = m;
  auto p = std::move(m);
  REQUIRE(std::equal(n.begin(), n.end(), p.begin()));
  REQUIRE(m.empty());
}

TEMPLATE_TEST_CASE("Addition", "[]", int, unsigned int, long, unsigned long,
                   float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  gsl::details::matrix_impl<TestType, false> n(r2.begin(), r2.end(), 100);
  REQUIRE(m.shape() == n.shape());
  auto p = m + n;
  std::transform(r1.begin(), r1.end(), r2.begin(), r1.begin(),
                 std::plus<void>());
  REQUIRE(std::equal(r1.begin(), r1.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Subtraction", "[]", int, unsigned int, long, unsigned long,
                   float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  gsl::details::matrix_impl<TestType, false> n(r2.begin(), r2.end(), 100);
  REQUIRE(m.shape() == n.shape());
  auto p = m - n;
  std::transform(r1.begin(), r1.end(), r2.begin(), r1.begin(),
                 std::minus<void>());
  REQUIRE(std::equal(r1.begin(), r1.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Muliplication", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 0, 10000);
  auto r2 = generate_random_seq<TestType>(10000, 0, 10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  gsl::details::matrix_impl<TestType, false> n(r2.begin(), r2.end(), 100);
  REQUIRE(m.shape() == n.shape());
  auto p = m * n;
  std::transform(r2.begin(), r2.end(), r1.begin(), r2.begin(),
                 std::multiplies<TestType>());
  REQUIRE(std::equal(r2.begin(), r2.end(), p.begin()));
  auto q = m * 5;
  std::for_each(r1.begin(), r1.end(), [](TestType &a) { a = a * 5; });
  REQUIRE(std::equal(r1.begin(), r1.end(), q.begin()));
}

TEMPLATE_TEST_CASE("Devision", "[]", int, unsigned int, long, unsigned long,
                   float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 1, 1000);
  auto r2 = generate_random_seq<TestType>(10000, 1, 1000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  gsl::details::matrix_impl<TestType, false> n(r2.begin(), r2.end(), 100);
  REQUIRE(m.shape() == n.shape());
  auto p = m / n;
  std::transform(r1.begin(), r1.end(), r2.begin(), r2.begin(),
                 std::divides<TestType>());
  REQUIRE(std::equal(r2.begin(), r2.end(), p.begin()));

  auto q = m / 5;
  std::for_each(r1.begin(), r1.end(), [](TestType &a) { a = a / 5; });
  REQUIRE(std::equal(r1.begin(), r1.end(), q.begin()));
}

TEMPLATE_TEST_CASE("MinMax operations", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  auto min_r1 = std::min_element(r1.begin(), r1.end());
  auto max_r1 = std::max_element(r1.begin(), r1.end());
  REQUIRE(*max_r1 == m.max());
  REQUIRE(*min_r1 == m.min());
  auto min_index =
      std::make_pair((size_t)std::distance(r1.begin(), min_r1) / 100,
                     (size_t)std::distance(r1.begin(), min_r1) % 100);
  REQUIRE(min_index == m.min_index());
}

TEMPLATE_TEST_CASE("Matrix Row extraction", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  for (size_t i = 0; i < m.num_rows(); ++i) {
    auto row = m.get_row(i);
    auto row_itr_start = m.begin() + i * m.num_cols();
    auto row_itr_end = row_itr_start + m.num_cols();
    REQUIRE((size_t)std::distance(row_itr_start, row_itr_end) == row.length());
    REQUIRE(std::equal(row_itr_start, row_itr_end, row.begin()));
  }
}
TEMPLATE_TEST_CASE("Matrix Col extraction", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  std::iota(r1.begin(), r1.end(), (TestType)0);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  for (size_t i = 0; i < m.num_cols(); ++i) {
    auto col = m.get_col(i);
    REQUIRE(col.length() == m.num_rows());
    auto start = m.begin() + i;
    for (size_t j = 0; j < m.num_rows(); ++j) {
      REQUIRE(*(col.begin() + j) == *(start + j * m.num_cols()));
    }
  }
}
