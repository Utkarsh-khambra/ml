#include "../../git/matplotlib-cpp/matplotlibcpp.h"
#include "logistic.hpp"
#include <algorithm>
#include <filesystem>
#include <rapidcsv.h>
#include <string>
namespace plt = matplotlibcpp;
template <size_t I> struct visit_impl {
  template <typename T, typename F>
  static void visit(T &tup, size_t idx, F fun) {
    if (idx == I - 1)
      fun(std::get<I - 1>(tup));
    else
      visit_impl<I - 1>::visit(tup, idx, fun);
  }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
template <> struct visit_impl<0> {
  template <typename T, typename F>
  static void visit(T &tup, size_t idx, F fun) {
    assert(false);
  }
};
#pragma GCC diagnostic pop

template <typename F, typename... Ts>
void visit_at(std::tuple<Ts...> const &tup, size_t idx, F fun) {
  visit_impl<sizeof...(Ts)>::visit(tup, idx, fun);
}

template <typename F, typename... Ts>
void visit_at(std::tuple<Ts...> &tup, size_t idx, F fun) {
  visit_impl<sizeof...(Ts)>::visit(tup, idx, fun);
}

void remove_punct(std::vector<std::string> &vec,
                  const std::vector<char> &punct) {
  std::for_each(vec.begin(), vec.end(), [&punct](std::string &str) {
    std::erase_if(str, [&punct](char val) -> bool {
      auto ret = std::find(punct.begin(), punct.end(), val);
      return ret != punct.end();
    });
  });
}

template <typename Vec>
auto count_list_of_words(const Vec &corpus, const Vec &list,
                         gsl::matrix<int> &store) {
  size_t row = 0, col = 0;
  for (auto i : list) {
    for (auto &j : corpus) {
      size_t step = 0, count = 0;
      while ((step = j.find(i, step)) != std::string::npos) {
        ++count;
        step += i.size();
      }
      store(row, col) = count;
      ++row;
    }
    row = 0;
    ++col;
  }
}

// Count the frequency of significant words in given data
template <typename... Ts>
auto count(std::tuple<std::vector<Ts>...> &tup, std::vector<int> indices,
           const std::vector<std::string> &words) {
  gsl::matrix<int> ret(std::get<0>(tup).size(), words.size());
  ret.set_all(0);
  for (auto j : indices) {
    visit_at(tup, j, [&ret, &words](auto &v) {
      if constexpr (std::is_same_v<std::string, typename std::decay_t<decltype(
                                                    v)>::value_type>)
        count_list_of_words(v, words, ret);
    });
  }
  return ret;
}

template <typename T, typename R>
void save(std::pair<gsl::matrix<T>, gsl::vector<R>> &tup, std::string name) {
  std::filesystem::create_directory(name);
  std::get<0>(tup).save(name + "/mat");
  std::get<1>(tup).save(name + "/vec");
}

void test_count() {
  auto p = std::make_tuple(std::vector<std::string>{
      "whar is this", "one two thr", "whar whar is", "is this"});
  std::vector<std::string> words{"whar", "is", "this"};
  auto g = count(p, {0}, words);
  g.print();
}

int main1() {
  std::string file("/home/utkarsh/ml/classification/amazon_baby.csv");
  std::tuple<std::vector<std::string>, std::vector<std::string>,
             std::vector<int>>
      products;
  rapidcsv::Document doc(file);

  std::get<0>(products) = doc.GetColumn<std::string>("name");
  std::get<1>(products) = doc.GetColumn<std::string>("review");
  std::get<2>(products) = doc.GetColumn<int>("rating");

  std::cout << "removing Punct\n";
  remove_punct(std::get<1>(products),
               {',', '\'', '.',  '!', '"', '#', '$', '%', '&', '*',
                '+', '-',  '/',  ':', ';', '<', '=', '>', '?', '@',
                '[', ']',  '\\', '^', '_', '`', '{', '}', '~'});
  std::cout << "Counting" << '\n';
  std::vector<std::string> sig_words{
      "love",         "great", "easy",    "old",   "little", "perfect", "loves",
      "well",         "able",  "car",     "broke", "less",   "even",    "waste",
      "disappointed", "work",  "product", "money", "would",  "return"};
  auto mat = count(products, {1}, sig_words);
  std::cout << "Appending output" << '\n';
  // Add output to mat matrix so that get_matrix_data will work
  std::vector<int> out(std::get<2>(products).begin(),
                       std::get<2>(products).end());
  for (auto &i : out)
    i = i <= 3 ? -1 : 1;
  gsl::matrix<int> temp(mat.num_rows(), mat.num_cols() + 1);
  for (size_t i = 0; i < mat.num_cols(); ++i) {
    auto col = mat.col_view(i);
    temp.set_col(i + 1, col);
  }
  temp.set_col(0, out);
  std::cout << "Moving\n";
  mat = std::move(temp);
  mat.print(10);
  std::vector<int> features(mat.num_cols() - 1);
  for (int ind = 1; auto &i : features) {
    i = ind++;
  }
  mat.save("data.mat");
  return 0;
}

auto load(std::string file, size_t rows, size_t cols, size_t row) {
  gsl::matrix<int> mat(rows, cols);
  gsl::vector<int> vec(row);
  mat.load(file + "/mat");
  vec.load(file + "/vec");
  return std::make_pair(mat, vec);
}

void test_prob() {
  gsl::matrix<double> d({1, 2, 3, 1, -1, -1}, 2);
  gsl::vector<double> e{1, 3, -1};
  gsl::vector<double> score{1 * 1 + 2 * 3 + -1 * 3,
                            1 * 1 + (-1) * 3 + (-1) * (-1)};
  gsl::vector<double> p{signum(score[0]), signum(score[1])};
  std::cout << "Correct :" << p[0] << " " << p[1] << '\n';
  auto r = predict_probability(d, e);
  std::cout << "correct?: " << r[0] << " " << r[1] << '\n';
}

void test_ll() {
  /* gsl::matrix<double> d({1, 2, 3, 1, -1, -1}, 2); */
  /* gsl::vector<double> e{1, 3, -1}; */
  /* gsl::vector<int> sentiment{-1, 1}; */
  /* std::cout << log_likelihood(d, sentiment, e) << '\n'; */
}

void plot(std::vector<double> &x) {
  /*std::vector<double> y{0,  1,   2,   3,   4,   5,   6,   7,   8,   9,   10,*/
  // 11, 12,  13,  15,  20,  30,  40,  50,  60,  70,  80,
  /*90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};*/
  int ind = -22 / 2;
  std::vector<double> y;
  for (size_t i = 0; i < 22; ++i) {
    y.push_back(ind++);
  }
  plt::plot(y, x);
}

void test_l2_reg(size_t num) {
  gsl::matrix<int> mat(183531, 21);
  mat.load("/home/utkarsh/ml/build/data.mat");
  std::vector<int> features{1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                            11, 12, 13, 14, 15, 16, 17, 18, 19};
  /* std::vector<int> features{1, 2}; */
  /* mat.print(100); */
  auto [data, output] = get_matrix_data(mat, features, 0);
  gsl::matrix<double> sub_data(data.begin(),
                               data.begin() + data.num_cols() * 50000, 50000);
  gsl::vector<int> sub_out(output.begin(), output.begin() + 50000);
  gsl::vector<double> weights(data.num_cols());
  gsl::vector<short> out(sub_out.length());
  std::for_each(out.begin(), out.end(), [&sub_out](short &a) {
    static size_t i = 0;
    a = static_cast<short>(sub_out[i++]);
  });
  /* gsl::vector<double> weights(data.num_cols()); */
  /* gsl::vector<short> out(output.begin(), output.end()); */
  std::vector<std::vector<double>> ws(weights.length() - 1,
                                      std::vector<double>(num));
  int ind = -num / 2;
  size_t ix = 0;
  for (; ix < num;) {
    weights.set_all(0);
    logistic_regression_l2(sub_data, out, weights, std::pow(10, ind++), 1e-7,
                           500);
    for (size_t i = 0; i < weights.length() - 1; i++) {
      ws[i][ix] = weights[i + 1];
    }
    auto score = predict_probability(sub_data, weights);
    auto classes = [](const gsl::vector<double> &in) {
      gsl::vector<short> ret(in.length());
      size_t s = 0;
      for (auto &i : ret)
        i = in[s++] >= 0.5 ? 1 : -1;
      return ret;
    }(score);
    classes = classes + out;
    auto right = std::count_if(classes.begin(), classes.end(),
                               [](short i) { return (i == 2) || (i == -2); });
    std::cout << "Accuracy For Model with l2 penalty " << pow(10, ind)
              << ":    " << right / (double)out.length() << '\n';
    ++ix;
  }
  plt::figure_size(1200, 780);
  plt::xlabel("L2 penalty");
  plt::ylabel("Weights");
  for (auto &i : ws) {
    plot(i);
  }
  plt::show();
}

int main() { test_l2_reg(22); }
