
#include <catch2/catch.hpp>
#include <execution>
#include <random>
#include <vector.hpp>
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

TEMPLATE_TEST_CASE("Vector View Test", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::vector<TestType> m(r1.begin(), r1.end());
  auto j = m.make_view(0, 100);
  auto k = m.make_view(22, 3012);
  REQUIRE(j.length() == 100);
  REQUIRE(k.length() == 3012 - 22);
}

TEMPLATE_TEST_CASE("Vector View Copy Test", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  gsl::vector<TestType> m(r1.begin(), r1.end());
  auto i = m.make_view(10, 1000);
  auto j(i);
  REQUIRE(i.length() == j.length());
  REQUIRE(std::equal(i.begin(), i.end(), j.begin()));
}

TEMPLATE_TEST_CASE("Vector View Addition", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::details::vector_impl<TestType, false> m(r1.begin(), r1.end());
  gsl::details::vector_impl<TestType, false> n(r2.begin(), r2.end());
  REQUIRE(m.length() == n.length());
  auto i = m.make_view(1012, 4050);
  auto j = n.make_view(1012, 4050);
  auto p = i + j;
  auto r = m.make_view(1012, 4050);
  REQUIRE(std::equal(r.begin(), r.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Vector View Subtraction", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::vector<TestType> m(r1.begin(), r1.end());
  gsl::vector<TestType> n(r2.begin(), r2.end());
  auto i = m.make_view(1245, 1050);
  auto j = n.make_view(1245, 1050);
  REQUIRE(i.length() == j.length());
  auto p = i - j;
  auto q = m.make_view(1245, 1050);
  REQUIRE(std::equal(q.begin(), q.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Vector View Muliplication", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 0, 10000);
  auto r2 = generate_random_seq<TestType>(10000, 0, 10000);
  gsl::vector<TestType> m(r1.begin(), r1.end());
  gsl::vector<TestType> n(r2.begin(), r2.end());
  auto i = m.make_view(4510, 5045);
  auto j = n.make_view(4510, 5045);
  REQUIRE(i.length() == j.length());
  auto p = i * j;
  REQUIRE(std::equal(p.begin(), p.end(), i.begin()));
  auto q = i * 5;
  REQUIRE(std::equal(q.begin(), q.end(), i.begin()));
}

TEMPLATE_TEST_CASE("Vector View Devision", "[]", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000, 1, 1000);
  auto r2 = generate_random_seq<TestType>(10000, 1, 1000);
  gsl::vector<TestType> m(r1.begin(), r1.end());
  gsl::vector<TestType> n(r2.begin(), r2.end());
  auto i = m.make_view(7810, 2189);
  auto j = n.make_view(7810, 2189);
  REQUIRE(i.length() == j.length());
  auto p = i / j;
  REQUIRE(std::equal(p.begin(), p.end(), i.begin()));
  auto q = j / 5;
  REQUIRE(std::equal(q.begin(), q.end(), j.begin()));
}
