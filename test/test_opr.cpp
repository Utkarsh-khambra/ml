#include <catch2/catch.hpp>
#include <execution>
#include <operations.hpp>
#include <vector>
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
TEMPLATE_TEST_CASE("Oper Cross operations", "", float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  gsl::matrix<TestType> n(r2.begin(), r2.end(), 100);
  REQUIRE(m.shape() == n.shape());
  auto p = gsl::cross(m, n);
  std::vector<TestType> test(10000, 0);
  for (auto i = 0; i < 100; ++i) {
    for (auto j = 0; j < 100; ++j) {
      for (auto k = 0; k < 100; ++k)
        test[100 * i + j] += r1[i * 100 + k] * r2[k * 100 + j];
    }
  }
  REQUIRE(std::equal(test.begin(), test.end(), p.begin()));
}

TEMPLATE_TEST_CASE("Oper Dot operations", "", int, unsigned int, long,
                   unsigned long, float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::vector<TestType> m(r1.begin(), r1.end());
  gsl::vector<TestType> n(r2.begin(), r2.end());
  REQUIRE(m.length() == n.length());
  auto p = gsl::dot(m, n);
  auto q = std::inner_product(r1.begin(), r1.end(), r2.begin(), (TestType)0);
  REQUIRE(p == q);
}

TEMPLATE_TEST_CASE("Matrix Vector Dot operations", "", float, double) {
  auto r1 = generate_random_seq<TestType>(10000);
  auto r2 = generate_random_seq<TestType>(10000);
  gsl::matrix<TestType> m(r1.begin(), r1.end(), 100);
  gsl::vector<TestType> n(r2.begin(), r2.begin() + 100);
  auto p = gsl::dot(m, n);
  gsl::vector<TestType> q(m.num_rows());
  REQUIRE(n.length() == 100);
  REQUIRE(m.shape() == std::pair<size_t, size_t>(100, 100));
  for (size_t i = 0; i < m.num_rows(); i += 1) {
    auto temp = m.get_row(i);
    q[i] = gsl::dot(temp, n);
  }
  REQUIRE(std::equal(p.begin(), p.end(), q.begin()));
}
/*TEMPLATE_TEST_CASE("Oper Norm2 operations", "", int, unsigned int, long,*/
// unsigned long, float, double) {
// auto r1 = generate_random_seq<TestType>(10000);
// gsl::vector<TestType> m(r1.begin(), r1.end());
// auto p = gsl::norm2(m);
// auto q = std::inner_product(r1.begin(), r1.end(), r1.begin(), (TestType)0);
// REQUIRE(p - (TestType)std::sqrt(q) < 0.0000001);
/*}*/
