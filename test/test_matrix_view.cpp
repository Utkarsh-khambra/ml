#include <catch2/catch.hpp>
#include <execution>
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

TEMPLATE_TEST_CASE("Matrix View Test", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  auto j = m.make_view(0, 0, 10, 10);
  auto k = m.make_view(2, 2, 30, 12);
  REQUIRE(j.shape() == std::pair<size_t, size_t>(10, 10));
  REQUIRE(k.shape() == std::pair<size_t, size_t>(30, 12));
}

TEMPLATE_TEST_CASE("Matrix View Copy Test", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  auto i = m.make_view(0, 0, 10, 10);
  REQUIRE(i.num_cols() == 10);
  REQUIRE(i.num_rows() == 10);
  auto j(i);
  REQUIRE(i.shape() == j.shape());
  REQUIRE(std::equal(i.begin(), i.end(), j.begin()));
}

TEMPLATE_TEST_CASE("Matrix View Addition", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::details::matrix_impl<TestType, false> m(r1.begin(), r1.end(), 100);
  gsl::details::matrix_impl<TestType, false> n(r2.begin(), r2.end(), 100);
  REQUIRE(m.shape() == n.shape());
  auto i = m.make_view(10, 12, 40, 50);
  auto j = n.make_view(10, 12, 40, 50);
  auto p = i + j;
  auto r = m.make_view(10, 12, 40, 50);
  REQUIRE(std::equal(r.begin(), r.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Matrix View Subtraction", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  gsl::matrix<TestType> n(r2.begin(), r2.end(), 100);
  auto i = m.make_view(12, 45, 10, 50);
  auto j = n.make_view(12, 45, 10, 50);
  REQUIRE(i.shape() == j.shape());
  auto p = i - j;
  auto q = m.make_view(12, 45, 10, 50);
  REQUIRE(std::equal(q.begin(), q.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Matrix View Muliplication", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 0, 10000);
  auto r2 = generate_random_seq<TestType>(10000, 0, 10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  gsl::matrix<TestType> n(r2.begin(), r2.end(), 100);
  auto i = m.make_view(45, 10, 50, 45);
  auto j = n.make_view(45, 10, 50, 45);
  REQUIRE(i.shape() == j.shape());
  auto p = i * j;
  REQUIRE(std::equal(p.begin(), p.end(), i.begin()));
  auto q = i * 5;
  REQUIRE(std::equal(q.begin(), q.end(), i.begin()));
}

TEMPLATE_TEST_CASE("Matrix View Devision", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 1, 1000);
  auto r2 = generate_random_seq<TestType>(10000, 1, 1000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  gsl::matrix<TestType> n(r2.begin(), r2.end(), 100);
  auto i = m.make_view(78, 10, 21, 89);
  auto j = n.make_view(78, 10, 21, 89);
  REQUIRE(i.shape() == j.shape());
  auto p = i / j;
  REQUIRE(std::equal(p.begin(), p.end(), i.begin()));
  auto q = j / 5;
  REQUIRE(std::equal(q.begin(), q.end(), j.begin()));
}

TEMPLATE_TEST_CASE("Matrix View Row", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 1, 1000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  for (size_t i = 0; i < m.num_rows(); ++i) {
    auto n = m.row_view(i);
    auto p = m.get_row(i);
    REQUIRE(std::equal(n.begin(), n.end(), p.begin()));
  }
}
TEMPLATE_TEST_CASE("Matrix View Col", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 1, 1000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  for (size_t i = 0; i < m.num_cols(); ++i) {
    auto n = m.col_view(i);
    auto p = m.get_col(i);
    REQUIRE(std::equal(n.cbegin(), n.cend(), p.begin()));
  }
}
