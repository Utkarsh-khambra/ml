#include <catch2/catch.hpp>
#include <execution>
#include <vector_impl.hpp>
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

TEST_CASE("Vector Iterator constructor check") {
  std::vector<double> a{1, 4, 7, 8, 9, 6, 47, 23, 456};
  gsl::details::vector_impl<double, false> m(a.begin(), a.end());
  REQUIRE(m.length() == 9);
}
TEST_CASE("Vector Initailizer list check") {
  gsl::details::vector_impl<double, false> m(
      {1, 4, 7, 54, 63, 48, 123, 457, 4});
  REQUIRE(m.length() == 9);
}
TEMPLATE_TEST_CASE("Vector Copy Constructor", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  auto n(m);
  REQUIRE(std::equal(m.begin(), m.end(), n.begin()));
}
TEMPLATE_TEST_CASE("Vector Move Constructor", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  auto n(m);
  auto p(std::move(m));
  REQUIRE(std::equal(n.begin(), n.end(), p.begin()));
  REQUIRE(m.empty());
}

TEMPLATE_TEST_CASE("Vector Copy Assignment Operator", "[]", int, unsigned int,
                   long, unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  auto n = m;
  REQUIRE(std::equal(n.begin(), n.end(), m.begin()));
}
TEMPLATE_TEST_CASE("Vector Move Assignment Operator", "[]", int, unsigned int,
                   long, unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  auto n = m;
  auto p = std::move(m);
  REQUIRE(std::equal(n.begin(), n.end(), p.begin()));
  REQUIRE(m.empty());
}

TEMPLATE_TEST_CASE("Vector Addition", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  gsl::details::vector_impl<TestType, false> n(r2.begin(), r2.end());
  REQUIRE(m.length() == n.length());
  auto p = m + n;
  std::transform(r1.begin(), r1.end(), r2.begin(), r1.begin(),
                 std::plus<void>());
  REQUIRE(std::equal(r1.begin(), r1.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Vector Subtraction", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  gsl::details::vector_impl<TestType, false> n(r2.begin(), r2.end());
  REQUIRE(m.length() == n.length());
  auto p = m - n;
  std::transform(r1.begin(), r1.end(), r2.begin(), r1.begin(),
                 std::minus<void>());
  REQUIRE(std::equal(r1.begin(), r1.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Vector Muliplication", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 0, 10000);
  auto r2 = generate_random_seq<TestType>(10000, 0, 10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  gsl::details::vector_impl<TestType, false> n(r2.begin(), r2.end());
  REQUIRE(m.length() == n.length());
  auto p = m * n;
  std::transform(r2.begin(), r2.end(), r1.begin(), r2.begin(),
                 std::multiplies<TestType>());
  REQUIRE(std::equal(r2.begin(), r2.end(), p.begin()));
  auto q = m * 5;
  std::for_each(r1.begin(), r1.end(), [](TestType &a) { a = a * 5; });
  REQUIRE(std::equal(r1.begin(), r1.end(), q.begin()));
}

TEMPLATE_TEST_CASE("Vector Devision", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 1, 1000);
  auto r2 = generate_random_seq<TestType>(10000, 1, 1000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  gsl::details::vector_impl<TestType, false> n(r2.begin(), r2.end());
  REQUIRE(m.length() == n.length());
  auto p = m / n;
  std::transform(r1.begin(), r1.end(), r2.begin(), r2.begin(),
                 std::divides<TestType>());
  REQUIRE(std::equal(r2.begin(), r2.end(), p.begin()));

  auto q = m / 5;
  std::for_each(r1.begin(), r1.end(), [](TestType &a) { a = a / 5; });
  REQUIRE(std::equal(r1.begin(), r1.end(), q.begin()));
}

TEMPLATE_TEST_CASE("Vector MinMax operations", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  auto min_r1 = std::min_element(r1.begin(), r1.end());
  auto max_r1 = std::max_element(r1.begin(), r1.end());
  REQUIRE(*max_r1 == m.max());
  REQUIRE(*min_r1 == m.min());
  auto min_index = (size_t)std::distance(r1.begin(), min_r1);
  REQUIRE(min_index == m.min_index());
}
