#include "regression.hpp"
#include <algorithm>
#include <iostream>
#include <random>
int main() {
  auto train = read_csv("/home/utkarsh/.ml/c2/week3/kc_house_train_data.csv");
  auto test = read_csv("/home/utkarsh/.ml/c2/week3/kc_house_test_data.csv");
  auto [a, b] = get_matrix_data(train, {3}, 0);
  gsl::vector<double> weights(a.num_cols());
  float step_size = 1e-12;
  int max_itr = 1000;
  gradient_decent(a, b, weights, step_size, 0, max_itr);
  std::cout << "Simple Weights\n";
  weights.print();
  gsl::vector<double> l2_big_weights(a.num_cols());
  gradient_decent(a, b, l2_big_weights, step_size, 1e8, max_itr);
  std::cout << "Big l2 penalty weights\n";
  l2_big_weights.print();

  auto [c, d] = get_matrix_data(train, {3, 16}, 0);
  gsl::vector<double> multi_weights(c.num_cols());
  gradient_decent(c, d, multi_weights, step_size, 0.0, max_itr);
  std::cout << "Simple multi feature weights\n";
  multi_weights.print();
  gsl::vector<double> big_penalty_multi_weights(c.num_cols());
  gradient_decent(c, d, big_penalty_multi_weights, step_size, 1e8, max_itr);
  std::cout << "Big penalty multi feature weights\n";
  big_penalty_multi_weights.print();
}
