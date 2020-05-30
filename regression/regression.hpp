#include <cmath>
#include <fstream>
#include <matrix.hpp>
#include <operations.hpp>
#include <ranges>
#include <sstream>
#include <vector.hpp>
gsl::matrix<double> read_csv(std::string file) {
  std::ifstream input_file(file);
  input_file.unsetf(std::ios_base::skipws);
  size_t num_rows = std::count(std::istream_iterator<char>(input_file),
                               std::istream_iterator<char>(), '\n') -
                    1;
  input_file.clear();
  input_file.seekg(0, std::ios_base::beg);
  input_file.setf(std::ios_base::skipws);
  std::string line;
  std::getline(input_file, line);
  size_t num_cols = std::count(line.begin(), line.end(), ',') + 1;
  gsl::matrix<double> ret(num_rows, num_cols);
  auto itr = ret.begin();
  while (std::getline(input_file, line)) {
    std::istringstream input(line);
    std::string word;
    while (std::getline(input, word, ',')) {
      *itr = std::stod(word);
      ++itr;
    }
  }
  return ret;
}

auto normalize_features(gsl::matrix<double> &features) {
  for (size_t i = 0; i < features.num_cols(); ++i) {
  }
}

auto get_matrix_data(const gsl::matrix<double> &data_set,
                     std::vector<int> features, int output) {
  auto itr = std::find(data_set.cbegin(), data_set.cend(), output);
  if (itr == data_set.cend())
    throw std::runtime_error("Ouput parameter should not be in parameter list");
  gsl::matrix<double> ret(data_set.num_rows(), std::size(features) + 1);
  // First column should be of ones
  for (auto i = ret.begin(); i != ret.end(); i += ret.num_cols())
    *i = 1;
  for (size_t i :
       std::views::iota((size_t)0) | std::views::take(data_set.num_rows())) {
    size_t index = 1;
    for (auto j : features) {
      ret(i, index) = data_set(i, j);
      ++index;
    }
  }
  gsl::vector<double> ret_vec(data_set.get_col(output));
  return std::make_pair(ret, ret_vec);
}

auto predict_outcome(const gsl::matrix<double> &features,
                     const gsl::vector<double> &weights) {
  return gsl::dot(features, weights);
}

double sum_squares(const gsl::vector<double> &a) {
  auto acc = std::inner_product(a.cbegin(), a.cend(), a.cbegin(), (double)0);
  return std::sqrt(acc);
}

double cost(const gsl::matrix<double> &features,
            const gsl::vector<double> &output,
            const gsl::vector<double> &weights, const double l2_penalty) {
  auto error = output - predict_outcome(features, weights);
  double cost =
      std::fma(l2_penalty,
               std::inner_product(weights.cbegin() + 1, weights.cend(),
                                  weights.cbegin() + 1, (double)0),
               gsl::dot(error, error));
  return cost;
}

auto derivative(const gsl::matrix<double> &features,
                const gsl::vector<double> &output,
                const gsl::vector<double> &weights,
                const double l2_penalty = 0) {
  gsl::vector<double> ret(features.num_cols());
  auto error = output - predict_outcome(features, weights);
  ret[0] = -std::accumulate(error.begin(), error.end(), (double)0);
  for (size_t i = 1; i < features.num_cols(); ++i)
    ret[i] = -gsl::dot(features.get_col(i), error) + l2_penalty * weights[i];
  return 2 * ret;
}

void gradient_decent(const gsl::matrix<double> &features,
                     const gsl::vector<double> &output,
                     gsl::vector<double> &weights, const float eta,
                     const double l2_penalty, int max_itr = 100) {
  assert(max_itr > 0);
  gsl::vector<double> der(features.num_cols());
  do {
    der = derivative(features, output, weights, l2_penalty);
    weights = weights - (eta * der);
    /* std::cout << "Iter: " << iter << " " << N << '\n'; */
    --max_itr;
  } while (max_itr > 0);
}
