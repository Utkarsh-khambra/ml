#pragma once
#include "impl_details.hpp"
#include <cassert>
#include <compare>
#include <functional>
#include <gsl/gsl_errno.h>
#include <iostream>
#include <vector_impl.hpp>
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
            base::free)) {
    std::copy(first, last, matrix->data);
  }
  matrix_impl(std::initializer_list<T> values,
              size_t num_rows) requires(!IsView)
      : matrix_impl(values.begin(), values.end(), num_rows) {}

  matrix_impl(size_t row, size_t col) requires(!IsView)
      : base(), matrix(uptr(base::allocate(row, col), base::free)) {}

  matrix_impl(const matrix_impl<T, false> &other)
      : matrix_impl(other.cbegin(), other.cend(), other.num_rows()) {
    /* std::cout << "Copy constructor\n"; */
  }

  matrix_impl(matrix_view_type view) : matrix(view) {}
  matrix_impl(const matrix_impl<T, true> &other) : matrix(other.matrix) {}
  matrix_impl(matrix_impl &&other) noexcept requires(!IsView)
      : matrix(std::move(other.matrix)) {}
  matrix_impl &operator=(matrix_impl other) {
    std::swap(matrix, other.matrix);
    return *this;
  }

  // Iterators
  class Iterator : public std::iterator<std::random_access_iterator_tag, T, T,
                                        const T *, T> {
  public:
    Iterator(matrix_type *mat, size_t row, size_t col)
        : ptr(mat), current_row(row), current_col(col) {}
    Iterator &operator++() noexcept {
      if (current_col + 1 >= ptr->size2) {
        current_col = 0;
        ++current_row;
      } else {
        ++current_col;
      }
      return *this;
    }
    Iterator &operator++(int) noexcept {
      auto ret(*this);
      if (current_col + 1 >= ptr->size2) {
        current_col = 0;
        ++current_row;
      } else {
        ++current_col;
      }
      return ret;
    }
    void print() {
      std::cout << current_col << '\n';
      std::cout << current_row << '\n';
    }
    Iterator &operator--() noexcept {
      if (current_col - 1 == 0) {
        current_col = ptr->size2 - 1;
        --current_row;
      } else {
        --current_col;
      }
      return *this;
    }
    Iterator &operator--(int) noexcept {
      auto ret(*this);
      if (current_col - 1 == 0) {
        current_col = ptr->size2 - 1;
        --current_row;
      } else {
        --current_col;
      }
      return ret;
    }
    Iterator operator+(int value) noexcept {
      bool exceed_col = (current_col + value) >= ptr->size2;
      if (exceed_col) {
        value -= (ptr->size2 - current_col);
        current_row = current_row + value / ptr->size2 + 1;
        current_col = value % ptr->size2;
      } else {
        current_col += value;
      }
      /* std::cout << ptr->size1 << " " << ptr->size2 << '\n'; */
      /* std::cout << current_row << " " << current_col << '\n'; */
      return *this;
    }
    T &operator*() noexcept {
      return *base::get_ptr(ptr, current_row, current_col);
    }
    bool operator==(const Iterator &other) const noexcept {
      return (ptr == other.ptr) && (current_col == other.current_col) &&
             (current_row == other.current_row);
    }
    auto operator<=>(const Iterator &other) const noexcept = default;

  private:
    matrix_type *ptr;
    size_t current_row;
    size_t current_col;
  };
  using iterator = std::conditional_t<IsView, Iterator, T *>;
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
  void set_all(T val) noexcept { base::set_all(mat_ptr(), val); }
  void set(size_t i, size_t j, T val) noexcept {
    base::set(mat_ptr(), i, j, val);
  }
  // TODO Change to make vector const
  void set_col(size_t i, std::vector<T> &col) {
    vector_impl<T, true> view(col.data(), col.size());
    auto result = base::set_col(mat_ptr(), i, view.get_vector());
    if (result)
      handle_exception(result);
  }
  void set_col(size_t i, vector_impl<T, true> &col) {
    auto result = base::set_col(mat_ptr(), i, col.get_vector());
    if (result)
      handle_exception(result);
  }
  void set_col(size_t i, vector_impl<T, false> &col) {
    base::set_col(mat_ptr(), i, col.get_vector());
  }
  iterator begin() noexcept {
    if constexpr (IsView)
      return iterator(mat_ptr(), 0, 0);
    else
      return mat_ptr()->data;
  }
  iterator end() noexcept { return begin() + num_cols() * num_rows(); }
  const iterator begin() const noexcept {
    if constexpr (IsView)
      return iterator(mat_ptr(), 0, 0);
    else
      return mat_ptr()->data;
  }
  const iterator end() const noexcept {
    return begin() + num_cols() * num_rows();
  }

  const iterator cbegin() const noexcept { return begin(); }
  const iterator cend() const noexcept { return end(); }
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
  vector_impl<T, false> get_row(size_t row) const {
    vector_impl<T, false> ret(num_cols());
    auto result = base::get_row(ret.get_vector(), mat_ptr(), row);
    if (result)
      handle_exception(result);
    return ret;
  }

  vector_impl<T, false> get_col(size_t col) const {
    vector_impl<T, false> ret(num_rows());
    auto result = base::get_col(ret.get_vector(), mat_ptr(), col);
    if (result)
      handle_exception(result);
    return ret;
  }
  void print() const noexcept {
    size_t row = 0;
    for (auto i = cbegin(); i != cend(); i += num_cols()) {
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
    for (auto i = cbegin(); i != cbegin() + rows * num_cols();
         i += num_cols()) {
      std::cout << "Row: " << row << " >> ";
      std::copy(i, i + num_cols(), std::ostream_iterator<T>(std::cout, " "));
      std::cout << '\n';
      ++row;
    }
  }
  void save(std::string file_name) {
    std::FILE *file = std::fopen(file_name.c_str(), "w");
    auto result = base::fwrite(file, mat_ptr());
    std::fclose(file);
    if (result)
      handle_exception(result);
  }
  void load(std::string file_name) {
    auto file = std::fopen(file_name.c_str(), "r");
    auto result = base::fread(file, mat_ptr());
    std::fclose(file);
    if (result)
      handle_exception(result);
  }
  auto make_view(size_t start_p, size_t start_q, size_t rows, size_t cols) {
    auto ret = base::submatrix(mat_ptr(), start_p, start_q, rows, cols);
    return matrix_impl<T, true>(ret);
  }

  auto row_view(size_t row, size_t offset = 0,
                std::optional<size_t> n = std::nullopt) {
    if (!n)
      return vector_impl<T, true>(base::row(mat_ptr(), row));
    else
      return vector_impl<T, true>(base::subrow(mat_ptr(), row, offset, *n));
    handle_exception(1000);
  }
  auto col_view(size_t col, size_t offset = 0,
                std::optional<size_t> n = std::nullopt) {
    if (!n)
      return vector_impl<T, true>(base::col(mat_ptr(), col));
    else
      return vector_impl<T, true>(base::subcol(mat_ptr(), col, offset, *n));
  }

private:
  std::conditional_t<IsView, matrix_view_type, uptr> matrix;
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
  void handle_exception(int result) const {
    std::cout << result << '\n';
    throw std::runtime_error("Error");
  }
};
} // namespace gsl::details
