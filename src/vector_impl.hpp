#pragma once
#include "impl_details.hpp"
#include <cassert>
#include <compare>
#include <functional>
#include <gsl/gsl_errno.h>
#include <iostream>
namespace gsl::details {
template <typename T, bool IsView>
requires(std::is_arithmetic_v<T>) class vector_impl
    : private gsl_vector_type<T> {
  using vector_view_type = typename gsl_vector_type<T>::view_type;
  using vector_type = typename gsl_vector_type<T>::type;
  using destructor = std::function<void(vector_type *)>;
  using uptr = std::unique_ptr<vector_type, destructor>;
  using base = gsl_vector_type<T>;

public:
  template <std::input_iterator Itr, bool b = IsView,
            std::enable_if_t<!b, int> = 0>
  vector_impl(Itr first, Itr last)
      : vector(uptr(base::allocate(std::distance(first, last)), base::free)) {
    std::copy(first, last, vec_ptr()->data);
  }
  vector_impl(std::initializer_list<T> values)
      : vector_impl(values.begin(), values.end()) {}

  vector_impl(size_t row)
      : base(), vector(uptr(base::allocate(row), base::free)) {}

  vector_impl(vector_view_type view) requires(IsView) : vector(view) {}

  vector_impl(const vector_impl &other) requires(!IsView)
      : vector_impl(other.cbegin(), other.cend()) {
    /* std::cout << "Copy constructor\n"; */
  }

  vector_impl(const vector_impl &other) requires(IsView)
      : vector(other.vector) {}

  vector_impl(vector_impl &&other) noexcept requires(!IsView)
      : vector(std::move(other.vector)) {}
  vector_impl &operator=(vector_impl other) {
    std::swap(vector, other.vector);
    return *this;
  }

  // Iterators
  class Iterator : public std::iterator<std::random_access_iterator_tag, T, T,
                                        const T *, T> {
  public:
    Iterator(vector_type *mat, size_t row) : ptr(mat), current_row(row) {}
    Iterator &operator++() noexcept {
      ++current_row;
      return *this;
    }
    Iterator &operator++(int) noexcept {
      auto ret(*this);
      ++current_row;
      return ret;
    }
    void print() { std::cout << current_row << '\n'; }
    Iterator &operator--() noexcept {
      --current_row;
      return *this;
    }
    Iterator &operator--(int) noexcept {
      auto ret(*this);
      --current_row;
      return ret;
    }
    Iterator operator+(int value) noexcept {
      current_row += value;
      /* std::cout << ptr->size1 << " " << ptr->size2 << '\n'; */
      /* std::cout << current_row << " " << current_col << '\n'; */
      return *this;
    }
    Iterator operator-(int value) noexcept { current_row -= value; }
    T &operator*() noexcept { return *base::get_ptr(ptr, current_row); }
    bool operator==(const Iterator &other) const noexcept {
      return (ptr == other.ptr) && (current_row == other.current_row);
    }
    auto operator<=>(const Iterator &other) const noexcept = default;

  private:
    vector_type *ptr;
    size_t current_row;
  };
  class ConstIterator : public std::iterator<std::random_access_iterator_tag, T,
                                             T, const T *, T> {
  public:
    ConstIterator(const vector_type *mat, size_t row)
        : ptr(mat), current_row(row) {}
    ConstIterator &operator++() noexcept {
      ++current_row;
      return *this;
    }
    ConstIterator &operator++(int) noexcept {
      auto ret(*this);
      ++current_row;
      return ret;
    }
    void print() { std::cout << current_row << '\n'; }
    ConstIterator &operator--() noexcept {
      --current_row;
      return *this;
    }
    ConstIterator &operator--(int) noexcept {
      auto ret(*this);
      --current_row;
      return ret;
    }
    ConstIterator operator+(int value) noexcept {
      current_row += value;
      /* std::cout << ptr->size1 << " " << ptr->size2 << '\n'; */
      /* std::cout << current_row << " " << current_col << '\n'; */
      return *this;
    }
    ConstIterator operator-(int value) noexcept { current_row -= value; }
    // Uses const_cast
    //  TODO Remove const_cast
    const T &operator*() const noexcept {
      return *base::get_ptr(const_cast<vector_type *>(ptr), current_row);
    }
    bool operator==(const ConstIterator &other) const noexcept {
      return (ptr == other.ptr) && (current_row == other.current_row);
    }
    ptrdiff_t operator-(const ConstIterator &other) noexcept {
      auto row_diff = static_cast<ptrdiff_t>(current_row - other.current_row);
      /* auto col_diff = static_cast<ptrdiff_t>(current_col-other.current_col);
       */
      return row_diff * ptr->stride;
    }
    auto operator<=>(const ConstIterator &other) const noexcept = default;

  private:
    const vector_type *ptr;
    size_t current_row;
  };
  using iterator = std::conditional_t<IsView, Iterator, T *>;
  using const_iterator = std::conditional_t<IsView, ConstIterator, const T *>;

  // Operators

  T &operator[](size_t row) noexcept { return *base::get_ptr(vec_ptr(), row); }
  const T &operator[](size_t row) const noexcept {
    return *base::get_ptr(vec_ptr(), row);
  }
  vector_impl operator+(const vector_impl &other) const {
    assert(other.shape() == shape());
    auto ret(*this);
    auto result = base::add(ret.vec_ptr(), other.vec_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }
  vector_impl operator+(const T value) const {
    auto ret(*this);
    auto result = base::add_constant(ret.vec_ptr(), value);
    if (result)
      handle_exception(result);
    return ret;
  }
  friend vector_impl operator+(const T value, const vector_impl &other) {
    return other + value;
  }
  vector_impl operator-(const vector_impl &other) const {
    assert(other.shape() == shape());
    auto ret(*this);
    auto result = base::sub(ret.vec_ptr(), other.vec_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }

  vector_impl operator-(const T value) const {
    auto ret(*this);
    auto result = base::add_constant(ret.vec_ptr(), -value);
    if (result)
      handle_exception(result);
    return ret;
  }

  friend vector_impl operator-(const T value, const vector_impl &other) {
    return other - value;
  }

  vector_impl operator*(const vector_impl &other) const {
    assert(shape() == other.shape());
    auto ret(*this);
    auto result = base::mul(ret.vec_ptr(), other.vec_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }
  friend vector_impl operator*(const T value, vector_impl mat) {
    return mat * value;
  }
  vector_impl operator*(const T value) const {
    auto ret(*this);
    auto result = base::scale(ret.vec_ptr(), value);
    if (result)
      handle_exception(result);
    return ret;
  }
  vector_impl operator/(const vector_impl &other) const {
    assert(shape() == other.shape());
    auto ret(*this);
    auto result = base::div(ret.vec_ptr(), other.vec_ptr());
    if (result)
      handle_exception(result);
    return ret;
  }

  vector_impl operator/(const T value) const {
    auto ret(*this);
    std::for_each(ret.begin(), ret.end(), [value](T &a) { a = a / value; });
    return ret;
  }

  // Functions
  auto get_vector() const noexcept { return vec_ptr(); }
  auto get_vector() noexcept { return vec_ptr(); }
  auto shape() const noexcept { return std::make_pair(length(), 1); }
  size_t length() const noexcept { return vec_ptr()->size; }
  iterator begin() noexcept {
    if constexpr (IsView)
      return iterator(vec_ptr(), 0);
    else
      return vec_ptr()->data;
  }
  iterator end() noexcept { return begin() + length(); }
  const_iterator begin() const noexcept {
    if constexpr (IsView)
      return const_iterator(vec_ptr(), 0);
    else
      return vec_ptr()->data;
  }
  const_iterator end() const noexcept { return begin() + length(); }

  const_iterator cbegin() const noexcept { return begin(); }
  const_iterator cend() const noexcept { return end(); }

  constexpr bool empty() const noexcept { return (vec_ptr() == nullptr); }
  constexpr T max() const noexcept { return base::max(vec_ptr()); }
  constexpr T min() const noexcept { return base::min(vec_ptr()); }
  constexpr auto minmax() const noexcept { return base::minmax(vec_ptr()); }
  constexpr auto min_index() const noexcept {
    return base::min_index(vec_ptr());
  }
  constexpr auto max_index() const noexcept {
    return base::max_index(vec_ptr());
  }
  constexpr auto minmax_index() const noexcept {
    return base::minmax_index(vec_ptr());
  }
  void print() const noexcept {
    std::copy(cbegin(), cend(), std::ostream_iterator<T>(std::cout, "\n"));
  }

  void print(size_t rows) const noexcept {
    if (rows > length())
      std::copy(cbegin(), cbegin() + rows,
                std::ostream_iterator<T>(std::cout, "\n"));
  }
  auto make_view(size_t offset = 0, size_t n = 0) {
    if (!n)
      n = length();
    auto ret = base::subvector(vec_ptr(), offset, n);
    return vector_impl<T, true>(ret);
  }

private:
  std::conditional_t<IsView, vector_view_type, uptr> vector;
  vector_type *vec_ptr() noexcept {
    if constexpr (IsView)
      return &vector.vector;
    else
      return vector.get();
  }
  const vector_type *vec_ptr() const noexcept {
    if constexpr (IsView)
      return &vector.vector;
    else
      return vector.get();
  }
  void handle_exception(int result) const {
    std::cout << result << '\n';
    throw std::runtime_error("Error");
  }
};
} // namespace gsl::details
