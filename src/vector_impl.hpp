#pragma once
#include "impl_details.hpp"
#include <functional>
#include <iostream>
namespace gsl::details {
template <typename T, bool StackStorage>
requires(std::is_arithmetic_v<T>) class vector_impl {
  using vector_view_type = typename gsl_vector_type<T>::view_type;

public:
  template <std::input_iterator Itr>
  requires(!StackStorage) vector_impl(Itr first, Itr last)
      : vector(unique_storage(func.constructor(std::distance(first, last)),
                              func.destructor)) {
    std::copy(first, last, vector->data);
  }
  vector_impl(std::initializer_list<T> values)
      : vector_impl(values.begin(), values.end()) {}

  vector_impl(size_t rows)
      : vector(unique_storage(func.constructor(rows), func.destructor)) {}

  vector_impl(const vector_impl &other) requires(!StackStorage)
      : vector_impl(other.cbegin(), other.cend()) {
    /* std::cout << "Copy constructor\n"; */
  }
  vector_impl(vector_view_type view) : vector_impl(view.vector){};
  vector_impl(const vector_impl &other) requires(StackStorage)
      : vector(other.vector) {}
  vector_impl(vector_impl &&other) noexcept requires(!StackStorage)
      : vector(std::move(other.vector.ptr)) {
    /* std::cout << "Move constructor\n"; */
  }
  vector_impl &operator=(vector_impl other) {
    std::swap(other.vector.ptr, vector.ptr);
    return *this;
  }

  // Operators

  T &operator[](size_t row) noexcept {
    return *func.get_ptr(vector.get(), row);
  }
  const T &operator[](size_t row) const noexcept {
    return *func.get_ptr(vector.get(), row);
  }
  vector_impl operator+(const vector_impl &other) const noexcept {
    assert(other.length() == length());
    auto ret(*this);
    func.add(ret.vector.get(), other.vector.get());
    return ret;
  }

  vector_impl operator+(const T value) const noexcept {
    auto ret(*this);
    func.add_constant(ret.vector.get(), value);
    return ret;
  }
  friend vector_impl operator+(const T value,
                               const vector_impl &other) noexcept {
    return other + value;
  }
  vector_impl operator-(const T value) const noexcept {
    auto ret(*this);
    func.add_constant(ret.vector.get(), -value);
    return ret;
  }
  friend vector_impl operator-(const T value,
                               const vector_impl &other) noexcept {
    return other - value;
  }
  vector_impl operator-(const vector_impl &other) const noexcept {
    assert(other.length() == length());
    auto ret(*this);
    func.sub(ret.vector.get(), other.vector.get());
    return ret;
  }
  vector_impl operator*(const vector_impl &other) const noexcept {
    assert(length() == other.length());
    auto ret(*this);
    func.mul(ret.vector.get(), other.vector.get());
    return ret;
  }
  vector_impl operator*(const T value) const noexcept {
    auto ret(*this);
    func.scale(ret.vector.get(), value);
    return ret;
  }
  vector_impl operator/(const vector_impl &other) const noexcept {
    assert(length() == other.length());
    auto ret(*this);
    func.div(ret.vector.get(), other.vector.get());
    return ret;
  }
  /*vector_impl operator*(const T value) const noexcept {*/
  // auto ret(*this);
  // func.scale(ret.vector.get(), value);
  // return ret;
  /*}*/
  vector_impl operator/(const T value) const noexcept {
    auto ret(*this);
    std::for_each(ret.begin(), ret.end(), [value](T &a) { a = a / value; });
    return ret;
  }
  friend vector_impl operator*(const T value, vector_impl mat) noexcept {
    return mat * value;
  }
  // Functions
  auto get_vector() const noexcept { return vector.get(); }
  auto get_vector() noexcept { return vector.get(); }
  size_t length() const noexcept { return vector->size; }
  T *begin() noexcept { return vector->data; }
  T *end() noexcept { return begin() + length(); }
  const T *begin() const noexcept { return cbegin(); }
  const T *end() const noexcept { return cend(); }
  const T *cbegin() const noexcept { return vector->data; }
  const T *cend() const noexcept { return vector->data + length(); }
  constexpr bool empty() const noexcept { return (vector.get() == nullptr); }
  constexpr T max() const noexcept { return func.max(vector.get()); }
  constexpr T min() const noexcept { return func.min(vector.get()); }
  constexpr auto minmax() const noexcept {
    T a, b;
    func.minmax(vector.get(), &a, &b);
    return std::make_pair(a, b);
  }
  constexpr auto min_index() const noexcept {
    return func.min_index(vector.get());
  }
  constexpr auto max_index() const noexcept {
    return func.max_index(vector.get());
  }
  constexpr auto minmax_index() const noexcept {
    size_t imin, imax;
    func.minmax_index(vector.get(), &imin, &imax);
    return std::make_pair(imin, imax);
  }
  void print() const noexcept {
    std::copy(cbegin(), cend(), std::ostream_iterator<T>(std::cout, "\n"));
  }
  void print(size_t num_rows) const noexcept {
    if (num_rows - 1 > length())
      num_rows = length() - 1;
    std::copy(cbegin(), cbegin() + num_rows,
              std::ostream_iterator<T>(std::cout, "\n"));
  }

  vector_impl<T, true> make_view(size_t offset, size_t n) noexcept {
    auto ret = func.subvector(vector.get(), offset, n);
    vector_impl<T, true> ret_vector(ret);
    return ret_vector;
  }

private:
  using vector_type = typename gsl_vector_type<T>::type;
  using destructor = std::function<void(vector_type *)>;
  using unique_storage = std::unique_ptr<vector_type, destructor>;
  Ptr<std::conditional_t<StackStorage, vector_type, unique_storage>> vector;
  auto constexpr static func = gsl_vector_type<T>();
  template <typename R, bool SType>
  requires(std::is_arithmetic_v<R>) friend class vector_impl;
  vector_impl(vector_type vec) : vector(vec) {}
};
} // namespace gsl::details
