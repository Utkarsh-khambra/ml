#pragma once
#include <cmath>
#include <fstream>
#include <matrix.hpp>
#include <operations.hpp>
#include <tuple>
#include <vector.hpp>
template <typename T>
auto get_matrix_data(gsl::matrix<T> &data, std::vector<int> features,
                     int output) {
  auto check = std::find(features.begin(), features.end(), output);
  if (check != features.end())
    throw std::runtime_error("Featue list must not contain output paramenter");
  auto cols = features.size() + 1;
  gsl::matrix<T> mat_ret(data.num_rows(), cols);
  mat_ret.set_all(1);
  size_t ind = 1;
  for (auto i : features) {
    auto v = data.col_view(i);
    mat_ret.set_col(ind, v);
    ++ind;
  }
  auto vec_ret = data.get_col(output);
  return std::make_pair(mat_ret, vec_ret);
}

double signum(double a) { return 1.0 / (1.0 + std::exp(-a)); }
template <typename T>
auto predict_probability(const gsl::matrix<T> &data,
                         const gsl::vector<double> &weights) {
  auto score = gsl::dot(data, weights);
  std::for_each(score.begin(), score.end(),
                [](std::common_type_t<T, double> &a) { a = signum(a); });
  return score;
}

// Error is indicatior variable - probability
template <typename T>
auto derivative(const gsl::matrix<T> &data, const gsl::vector<double> &error) {
  gsl::vector<double> ret(data.num_cols());
  size_t ind = 0;
  while (ind < data.num_cols()) {
    auto col = data.get_col(ind);
    ret[ind] = gsl::dot(col, error);
    ++ind;
  }
  return ret;
}

template <typename T>
auto log_likelihood(const gsl::matrix<T> &data,
                    const gsl::vector<short> &sentiment,
                    const gsl::vector<double> &weights) {
  auto score = gsl::dot(data, weights);
  gsl::vector<short> indicatior(sentiment.length());
  size_t ind = 0;
  std::generate(indicatior.begin(), indicatior.end(), [&ind, &sentiment]() {
    return static_cast<short>(sentiment[ind++] == 1) - 1;
  });
  auto prod1 = indicatior * score;
  std::for_each(score.begin(), score.end(),
                [](double &a) { a = std::log(1 + std::exp(-a)); });
  prod1 = prod1 - score;
  return std::accumulate(prod1.begin(), prod1.end(), (double)0);
}

template <typename T>
auto logistic_regression(const gsl::matrix<T> &data,
                         const gsl::vector<short> &sentiment,
                         gsl::vector<double> &weights, double step_size,
                         size_t max_iter) {
  std::vector<double> ll;
  gsl::vector<short> indicatior(sentiment.length());
  std::generate(indicatior.begin(), indicatior.end(), [&sentiment]() {
    static size_t ind = 0;
    return static_cast<short>(sentiment[ind++] == 1);
  });
  for (size_t i = 0; i < max_iter; ++i) {
    auto probability = predict_probability(data, weights);
    auto error = indicatior - probability;
    auto der = derivative(data, error);
    weights = weights + step_size * der;
    if (i <= 15 || (i <= 100 and i % 10 == 0) || (i <= 1000 and i % 100 == 0) ||
        (i <= 10000 and i % 1000 == 0)) {
      std::cout << "Iteration:" << i << '\n';
      ll.push_back(log_likelihood(data, sentiment, weights));
    }
  }
  return ll;
}

template <typename T>
auto derivative(const gsl::matrix<T> &data, const gsl::vector<double> &error,
                const gsl::vector<double> &weights, double l2_penalty) {
  gsl::vector<double> ret(weights.length());
  ret[0] = std::accumulate(error.begin(), error.end(), (double)0);
  size_t i = 1;
  while (i < data.num_cols()) {
    auto col = data.get_col(i);
    ret[i] = gsl::dot(col, error) - 2 * l2_penalty * weights[i];
    ++i;
  }
  return ret;
}
template <typename T>
auto log_likelihood(const gsl::matrix<T> &data,
                    const gsl::vector<short> &sentiment,
                    const gsl::vector<double> &weights, double l2_penalty) {
  auto score = gsl::dot(data, weights);
  gsl::vector<short> indicatior(sentiment.length());
  size_t ind = 0;
  std::generate(indicatior.begin(), indicatior.end(), [&ind, &sentiment]() {
    return static_cast<short>(sentiment[ind++] == 1) - 1;
  });
  auto prod1 = indicatior * score;
  std::for_each(score.begin(), score.end(),
                [](double &a) { a = std::log(1 + std::exp(-a)); });
  prod1 = prod1 - score;
  for (size_t i = 1; i < data.num_cols(); ++i)
    prod1[i] = prod1[i] - l2_penalty * weights[i] * weights[i];
  return std::accumulate(prod1.begin(), prod1.end(), (double)0);
}
template <typename T>
auto logistic_regression_l2(const gsl::matrix<T> &data,
                            const gsl::vector<short> &sentiment,
                            gsl::vector<double> &weights, double l2_penalty,
                            double step_size, size_t max_iter) {
  std::vector<double> ll;
  gsl::vector<short> indicatior(sentiment.length());
  size_t ind = 0;
  std::generate(indicatior.begin(), indicatior.end(), [&sentiment, &ind]() {
    return static_cast<short>(sentiment[ind++] == 1);
  });
  for (size_t i = 0; i < max_iter; ++i) {
    auto probability = predict_probability(data, weights);
    auto error = indicatior - probability;
    auto der = derivative(data, error, weights, l2_penalty);
    weights = weights + step_size * der;
    if (i <= 15 || (i <= 100 and i % 10 == 0) || (i <= 1000 and i % 100 == 0) ||
        (i <= 10000 and i % 1000 == 0)) {
      /* std::cout << "Iteration:" << i << '\n'; */
      ll.push_back(log_likelihood(data, sentiment, weights, l2_penalty));
    }
  }
  return ll;
}
