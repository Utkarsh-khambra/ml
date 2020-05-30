
#pragma once
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <memory>
#include <type_traits>
namespace gsl {
namespace details {

template <typename R> struct gsl_vector_type {};
template <> struct gsl_vector_type<char> {
private:
  using inst_type = char;

public:
  using type = gsl_vector_char;
  using view_type = gsl_vector_char_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_char_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_char_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_char_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_char_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_char_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_char_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_char_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_char_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_char_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_char_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_char_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_char_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_char_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_char_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_char_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_char_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_char_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_char_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_char_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_char_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_char_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_char_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_char_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_char_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_char_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_char_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_char_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_char_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_char_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_char_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_char_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_char_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_char_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_char_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_char_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_char_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_char_equal(vec, other);
  };
};
template <> struct gsl_vector_type<unsigned char> {
private:
  using inst_type = unsigned char;

public:
  using type = gsl_vector_uchar;
  using view_type = gsl_vector_uchar_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_uchar_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_uchar_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_uchar_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_uchar_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_uchar_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_uchar_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_uchar_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_uchar_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_uchar_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_uchar_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_uchar_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_uchar_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_uchar_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_uchar_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_uchar_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_uchar_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_uchar_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_uchar_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_uchar_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_uchar_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_uchar_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_uchar_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_uchar_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_uchar_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_uchar_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_uchar_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_uchar_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_uchar_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_uchar_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_uchar_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_uchar_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_uchar_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_uchar_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_uchar_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_uchar_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_uchar_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_uchar_equal(vec, other);
  };
};

template <> struct gsl_vector_type<short> {
private:
  using inst_type = short;

public:
  using type = gsl_vector_short;
  using view_type = gsl_vector_short_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_short_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_short_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_short_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_short_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_short_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_short_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_short_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_short_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_short_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_short_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_short_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_short_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_short_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_short_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_short_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_short_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_short_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_short_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_short_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_short_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_short_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_short_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_short_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_short_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_short_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_short_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_short_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_short_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_short_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_short_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_short_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_short_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_short_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_short_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_short_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_short_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_short_equal(vec, other);
  };
};

template <> struct gsl_vector_type<unsigned short> {
private:
  using inst_type = unsigned short;

public:
  using type = gsl_vector_ushort;
  using view_type = gsl_vector_ushort_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_ushort_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_ushort_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_ushort_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ushort_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_ushort_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ushort_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_ushort_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_ushort_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ushort_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_ushort_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_ushort_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_ushort_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_ushort_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_ushort_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_ushort_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_ushort_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_ushort_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_ushort_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_ushort_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_ushort_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_ushort_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_ushort_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_ushort_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_ushort_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_ushort_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_ushort_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_ushort_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_ushort_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_ushort_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_ushort_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_ushort_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_ushort_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_ushort_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_ushort_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_ushort_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_ushort_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_ushort_equal(vec, other);
  };
};

template <> struct gsl_vector_type<int> {
private:
  using inst_type = int;

public:
  using type = gsl_vector_int;
  using view_type = gsl_vector_int_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_int_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_int_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_int_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_int_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_int_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_int_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_int_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_int_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_int_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_int_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_int_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_int_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_int_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_int_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_int_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_int_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_int_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_int_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_int_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_int_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_int_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_int_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_int_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_int_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_int_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_int_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_int_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_int_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_int_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_int_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_int_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_int_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_int_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_int_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_int_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_int_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_int_equal(vec, other);
  };
};

template <> struct gsl_vector_type<unsigned int> {
private:
  using inst_type = unsigned int;

public:
  using type = gsl_vector_uint;
  using view_type = gsl_vector_uint_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_uint_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_uint_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_uint_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_uint_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_uint_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_uint_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_uint_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_uint_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_uint_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_uint_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_uint_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_uint_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_uint_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_uint_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_uint_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_uint_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_uint_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_uint_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_uint_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_uint_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_uint_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_uint_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_uint_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_uint_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_uint_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_uint_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_uint_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_uint_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_uint_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_uint_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_uint_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_uint_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_uint_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_uint_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_uint_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_uint_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_uint_equal(vec, other);
  };
};

template <> struct gsl_vector_type<long> {
private:
  using inst_type = long;

public:
  using type = gsl_vector_long;
  using view_type = gsl_vector_long_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_long_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_long_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_long_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_long_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_long_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_long_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_long_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_long_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_long_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_long_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_long_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_long_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_long_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_long_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_long_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_long_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_long_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_long_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_long_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_long_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_long_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_long_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_long_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_long_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_long_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_long_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_long_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_long_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_long_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_long_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_long_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_long_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_long_equal(vec, other);
  };
};

template <> struct gsl_vector_type<unsigned long> {
private:
  using inst_type = unsigned long;

public:
  using type = gsl_vector_ulong;
  using view_type = gsl_vector_ulong_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_ulong_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_ulong_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_ulong_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ulong_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_ulong_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ulong_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_ulong_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_ulong_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ulong_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_ulong_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_ulong_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_ulong_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_ulong_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_ulong_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_ulong_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_ulong_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_ulong_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_ulong_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_ulong_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_ulong_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_ulong_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_ulong_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_ulong_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_ulong_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_ulong_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_ulong_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_ulong_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_ulong_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_ulong_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_ulong_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_ulong_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_ulong_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_ulong_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_ulong_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_ulong_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_ulong_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_ulong_equal(vec, other);
  };
};

template <> struct gsl_vector_type<float> {
private:
  using inst_type = float;

public:
  using type = gsl_vector_float;
  using view_type = gsl_vector_float_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_float_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_float_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_float_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_float_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_float_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_float_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_float_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_float_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_float_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_float_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_float_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_float_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_float_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_float_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_float_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_float_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_float_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_float_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_float_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_float_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_float_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_float_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_float_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_float_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_float_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_float_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_float_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_float_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_float_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_float_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_float_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_float_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_float_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_float_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_float_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_float_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_float_equal(vec, other);
  };
};

template <> struct gsl_vector_type<double> {
private:
  using inst_type = double;

public:
  using type = gsl_vector;
  using view_type = gsl_vector_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride =
      [](ptr vec, size_t offset, size_t stride, size_t n) noexcept {
        return gsl_vector_subvector_with_stride(vec, offset, stride, n);
      };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_equal(vec, other);
  };
};

template <> struct gsl_vector_type<long double> {
private:
  using inst_type = long double;

public:
  using type = gsl_vector_long_double;
  using view_type = gsl_vector_long_double_view;
  using ptr = type *;
  constexpr static auto allocate = [](size_t size) noexcept {
    return gsl_vector_long_double_alloc(size);
  };
  constexpr static auto deallocate = [](type *vec) noexcept {
    return gsl_vector_long_double_free(vec);
  };
  constexpr static auto calloc = [](size_t size) noexcept {
    return gsl_vector_long_double_calloc(size);
  };
  constexpr static auto get = [](ptr vec, size_t row) noexcept {
    return gsl_vector_long_double_get(vec, row);
  };
  constexpr static auto set = [](ptr vec, size_t row, auto value) noexcept {
    gsl_vector_long_double_set(vec, row, value);
  };
  constexpr static auto get_ptr = [](ptr vec, size_t row) noexcept {
    return gsl_vector_long_double_ptr(vec, row);
  };
  constexpr static auto set_all = [](ptr vec, auto value) noexcept {
    gsl_vector_long_double_set_all(vec, value);
  };
  constexpr static auto set_zero = [](ptr vec) noexcept {
    gsl_vector_long_double_set_zero(vec);
  };
  constexpr static auto set_baseic = [](ptr vec, size_t row) noexcept {
    return gsl_vector_long_double_set_basis(vec, row);
  };
  constexpr static auto fwrite = [](FILE *stream, const ptr vec) noexcept {
    return gsl_vector_long_double_fwrite(stream, vec);
  };
  constexpr static auto fread = [](FILE *stream, ptr vec) noexcept {
    return gsl_vector_long_double_fread(stream, vec);
  };
  constexpr static auto subvector = [](ptr vec, size_t offset,
                                       size_t n) noexcept {
    return gsl_vector_long_double_subvector(vec, offset, n);
  };
  constexpr static auto subvector_with_stride = [](ptr vec, size_t offset,
                                                   size_t stride,
                                                   size_t n) noexcept {
    return gsl_vector_long_double_subvector_with_stride(vec, offset, stride, n);
  };
  constexpr static auto view_array = [](auto *base, size_t n) noexcept {
    return gsl_vector_long_double_view_array(base, n);
  };
  constexpr static auto view_array_with_stride = [](auto *base, size_t stride,
                                                    size_t n) noexcept {
    return gsl_vector_long_double_view_array_with_stride(base, stride, n);
  };
  constexpr static auto memcpy = [](type *dest, const type *src) noexcept {
    return gsl_vector_long_double_memcpy(dest, src);
  };
  constexpr static auto swap = [](type *dest, type *src) noexcept {
    return gsl_vector_long_double_swap(dest, src);
  };
  constexpr static auto swap_elements = [](type *dest, size_t i,
                                           size_t j) noexcept {
    return gsl_vector_long_double_swap_elements(dest, i, j);
  };
  constexpr static auto reverse = [](type *dest) noexcept {
    return gsl_vector_long_double_reverse(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_vector_long_double_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_vector_long_double_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_vector_long_double_mul(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_vector_long_double_div(a, b);
  };
  constexpr static auto scale = [](type *a, const auto b) noexcept {
    return gsl_vector_long_double_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const auto b) noexcept {
    return gsl_vector_long_double_add_constant(a, b);
  };
  constexpr static auto axpby = [](const auto a, const type *v, const auto b,
                                   type *w) noexcept {
    static_assert(std::is_same_v<decltype(a), decltype(b)>,
                  "Both constants must be of same type");
    return gsl_vector_long_double_axpby(a, v, b, w);
  };
  constexpr static auto max = [](const type *a) noexcept {
    return gsl_vector_long_double_max(a);
  };
  constexpr static auto min = [](const type *a) noexcept {
    return gsl_vector_long_double_min(a);
  };
  constexpr static auto minmax = [](const type *vec) noexcept {
    inst_type a, b;
    gsl_vector_long_double_minmax(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *vec) noexcept {
    return gsl_vector_long_double_min_index(vec);
  };
  constexpr static auto max_index = [](const type *vec) noexcept {
    return gsl_vector_long_double_max_index(vec);
  };
  constexpr static auto minmax_index = [](const type *vec) noexcept {
    size_t a, b;
    gsl_vector_long_double_minmax_index(vec, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto ispos = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_double_ispos(vec);
  };
  constexpr static auto isneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_double_isneg(vec);
  };
  constexpr static auto isnull = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_double_isnull(vec);
  };
  constexpr static auto isnonneg = [](const type *vec) noexcept -> bool {
    return gsl_vector_long_double_isnonneg(vec);
  };
  constexpr static auto equal = [](const type *vec,
                                   const type *other) noexcept -> bool {
    return gsl_vector_long_double_equal(vec, other);
  };
};

// Start Matrix Declarations
template <typename R> struct gsl_matrix_type {};
template <> struct gsl_matrix_type<char> {
private:
  using inst_type = char;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_char;
  using view_type = gsl_matrix_char_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_char_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_char_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_char_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_char_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_char_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_char_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_char_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_char_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_char_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_char_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_char_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_char_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_char_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_char_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_char_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_char_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_char_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_char_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_char_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_char_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_char_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_char_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_char_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_char_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_char_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_char_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_char_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_char_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_char_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_char_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_char_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_char_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_char_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_char_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_char_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_char_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_char_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_char_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_char_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_char_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_char_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_char_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_char_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_char_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_char_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_char_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_char_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_char_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_char_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<unsigned char> {
private:
  using inst_type = unsigned char;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_uchar;
  using view_type = gsl_matrix_uchar_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_uchar_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_uchar_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_uchar_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_uchar_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_uchar_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_uchar_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_uchar_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_uchar_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_uchar_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_uchar_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_uchar_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_uchar_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_uchar_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_uchar_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_uchar_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_uchar_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uchar_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uchar_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_uchar_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_uchar_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_uchar_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uchar_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uchar_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_uchar_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_uchar_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_uchar_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_uchar_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_uchar_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_uchar_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_uchar_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_uchar_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_uchar_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_uchar_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_uchar_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_uchar_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_uchar_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_uchar_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_uchar_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_uchar_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_uchar_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_uchar_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_uchar_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_uchar_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_uchar_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uchar_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uchar_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uchar_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uchar_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_uchar_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<short> {
private:
  using inst_type = short;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_short;
  using view_type = gsl_matrix_short_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_short_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_short_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_short_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_short_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_short_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_short_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_short_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_short_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_short_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_short_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_short_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_short_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_short_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_short_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_short_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_short_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_short_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_short_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_short_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_short_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_short_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_short_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_short_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_short_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_short_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_short_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_short_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_short_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_short_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_short_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_short_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_short_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_short_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_short_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_short_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_short_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_short_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_short_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_short_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_short_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_short_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_short_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_short_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_short_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_short_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_short_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_short_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_short_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_short_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<unsigned short> {
private:
  using inst_type = unsigned short;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_ushort;
  using view_type = gsl_matrix_ushort_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_ushort_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_ushort_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_ushort_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_ushort_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_ushort_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_ushort_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_ushort_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_ushort_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_ushort_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_ushort_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_ushort_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_ushort_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_ushort_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_ushort_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_ushort_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_ushort_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ushort_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ushort_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_ushort_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_ushort_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_ushort_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ushort_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ushort_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_ushort_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_ushort_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_ushort_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_ushort_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_ushort_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_ushort_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_ushort_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_ushort_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_ushort_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_ushort_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_ushort_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_ushort_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_ushort_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_ushort_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_ushort_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_ushort_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_ushort_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_ushort_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_ushort_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_ushort_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_ushort_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ushort_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ushort_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ushort_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ushort_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_ushort_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<int> {
private:
  using inst_type = int;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_int;
  using view_type = gsl_matrix_int_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_int_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_int_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_int_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_int_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_int_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_int_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_int_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_int_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_int_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_int_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_int_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_int_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_int_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_int_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_int_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_int_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_int_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_int_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_int_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_int_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_int_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_int_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_int_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_int_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_int_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_int_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_int_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_int_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_int_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_int_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_int_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_int_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_int_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_int_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_int_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_int_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_int_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_int_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_int_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_int_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_int_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_int_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_int_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_int_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_int_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_int_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_int_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_int_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_int_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<unsigned int> {
private:
  using inst_type = unsigned int;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_uint;
  using view_type = gsl_matrix_uint_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_uint_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_uint_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_uint_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_uint_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_uint_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_uint_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_uint_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_uint_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_uint_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_uint_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_uint_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_uint_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_uint_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_uint_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_uint_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_uint_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uint_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uint_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_uint_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_uint_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_uint_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uint_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_uint_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_uint_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_uint_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_uint_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_uint_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_uint_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_uint_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_uint_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_uint_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_uint_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_uint_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_uint_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_uint_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_uint_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_uint_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_uint_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_uint_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_uint_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_uint_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_uint_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_uint_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_uint_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uint_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uint_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uint_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_uint_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_uint_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<long> {
private:
  using inst_type = long;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_long;
  using view_type = gsl_matrix_long_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_long_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_long_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_long_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_long_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_long_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_long_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_long_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_long_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_long_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_long_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_long_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_long_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_long_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_long_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_long_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_long_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_long_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_long_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_long_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_long_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_long_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_long_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_long_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_long_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_long_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_long_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_long_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_long_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_long_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_long_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_long_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_long_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_long_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_long_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_long_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_long_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_long_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<unsigned long> {
private:
  using inst_type = unsigned long;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_ulong;
  using view_type = gsl_matrix_ulong_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_ulong_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_ulong_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_ulong_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_ulong_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_ulong_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_ulong_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_ulong_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_ulong_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_ulong_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_ulong_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_ulong_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_ulong_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_ulong_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_ulong_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_ulong_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_ulong_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ulong_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ulong_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_ulong_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_ulong_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_ulong_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ulong_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_ulong_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_ulong_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_ulong_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_ulong_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_ulong_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_ulong_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_ulong_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_ulong_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_ulong_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_ulong_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_ulong_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_ulong_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_ulong_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_ulong_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_ulong_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_ulong_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_ulong_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_ulong_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_ulong_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_ulong_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_ulong_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_ulong_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ulong_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ulong_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ulong_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ulong_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_ulong_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<float> {
private:
  using inst_type = float;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_float;
  using view_type = gsl_matrix_float_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_float_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_float_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_float_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_float_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_float_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_float_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_float_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_float_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_float_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_float_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_float_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_float_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_float_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_float_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_float_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_float_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_float_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_float_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_float_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_float_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_float_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_float_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_float_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_float_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_float_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_float_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_float_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_float_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_float_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_float_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_float_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_float_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_float_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_float_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_float_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_float_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_float_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_float_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_float_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_float_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_float_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_float_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_float_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_float_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_float_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_float_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_float_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_float_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_float_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<double> {
private:
  using inst_type = double;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix;
  using view_type = gsl_matrix_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept { gsl_matrix_free(mat); };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_equal(mat, other);
  };
};

template <> struct gsl_matrix_type<long double> {
private:
  using inst_type = long double;
  using vector = gsl_vector_type<inst_type>::type;

public:
  using type = gsl_matrix_long_double;
  using view_type = gsl_matrix_long_double_view;
  using ptr = type *;

  constexpr static auto allocate = [](size_t row, size_t col) noexcept {
    return gsl_matrix_long_double_alloc(row, col);
  };
  constexpr static auto calloc = [](size_t row, size_t col) noexcept {
    return gsl_matrix_long_double_calloc(row, col);
  };
  constexpr static auto free = [](ptr mat) noexcept {
    gsl_matrix_long_double_free(mat);
  };
  constexpr static auto get = [](const ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_long_double_get(mat, i, j);
  };
  constexpr static auto set = [](ptr mat, size_t i, size_t j,
                                 auto val) noexcept {
    gsl_matrix_long_double_set(mat, i, j, val);
  };
  constexpr static auto get_ptr = [](ptr mat, size_t i, size_t j) noexcept {
    return gsl_matrix_long_double_ptr(mat, i, j);
  };
  constexpr static auto set_all = [](ptr mat, auto val) noexcept {
    gsl_matrix_long_double_set_all(mat, val);
  };
  constexpr static auto set_zero = [](ptr mat) noexcept {
    gsl_matrix_long_double_set_zero(mat);
  };
  constexpr static auto identity = [](ptr mat) noexcept {
    gsl_matrix_long_double_set_identity(mat);
  };
  constexpr static auto fwrite = [](FILE *file, const ptr mat) noexcept {
    return gsl_matrix_long_double_fwrite(file, mat);
  };
  constexpr static auto fread = [](FILE *file, ptr mat) noexcept {
    return gsl_matrix_long_double_fread(file, mat);
  };
  constexpr static auto submatrix = [](ptr mat, size_t p1, size_t p2, size_t k1,
                                       size_t k2) noexcept {
    return gsl_matrix_long_double_submatrix(mat, p1, p2, k1, k2);
  };
  constexpr static auto view_array = [](auto *base, size_t k1,
                                        size_t k2) noexcept {
    return gsl_matrix_long_double_view_array(base, k1, k2);
  };
  constexpr static auto view_array_with_tda =
      [](auto *base, size_t k1, size_t k2, size_t tda) noexcept {
        return gsl_matrix_long_double_view_array_with_tda(base, k1, k2, tda);
      };
  constexpr static auto view_vector = [](gsl_vector_type<inst_type>::type *vec,
                                         size_t k1, size_t k2) noexcept {
    return gsl_matrix_long_double_view_vector(vec, k1, k2);
  };
  constexpr static auto view_vector_with_tda =
      [](gsl_vector_type<inst_type>::type *vec, size_t k1, size_t k2,
         size_t tda) noexcept {
        return gsl_matrix_long_double_view_vector_with_tda(vec, k1, k2, tda);
      };
  constexpr static auto row = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_double_row(mat, k);
  };
  constexpr static auto col = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_double_column(mat, k);
  };
  constexpr static auto subrow = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_long_double_subrow(mat, k, offset, n);
  };
  constexpr static auto subcol = [](type *mat, size_t k, size_t offset,
                                    size_t n) noexcept {
    return gsl_matrix_long_double_subcolumn(mat, k, offset, n);
  };
  constexpr static auto diagonal = [](type *mat) noexcept {
    return gsl_matrix_long_double_diagonal(mat);
  };
  constexpr static auto subdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_double_subdiagonal(mat, k);
  };
  constexpr static auto supdiagonal = [](type *mat, size_t k) noexcept {
    return gsl_matrix_long_double_superdiagonal(mat, k);
  };
  constexpr static auto get_row = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_long_double_get_row(vec, mat, k);
  };
  constexpr static auto get_col = [](vector *vec, const type *mat,
                                     size_t k) noexcept {
    return gsl_matrix_long_double_get_col(vec, mat, k);
  };
  constexpr static auto set_col = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_long_double_set_col(mat, k, vec);
  };
  constexpr static auto set_row = [](type *mat, size_t k,
                                     const vector *vec) noexcept {
    return gsl_matrix_long_double_set_row(mat, k, vec);
  };
  constexpr static auto swap_row = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_long_double_swap_rows(mat, k, j);
  };
  constexpr static auto swap_col = [](type *mat, size_t k, size_t j) noexcept {
    return gsl_matrix_long_double_swap_columns(mat, k, j);
  };
  constexpr static auto swap_row_col = [](type *mat, size_t k,
                                          size_t j) noexcept {
    return gsl_matrix_long_double_swap_rowcol(mat, k, j);
  };
  constexpr static auto transpose_memcpy = [](type *dest,
                                              const type *src) noexcept {
    return gsl_matrix_long_double_transpose_memcpy(dest, src);
  };
  constexpr static auto transpose = [](type *dest) noexcept {
    return gsl_matrix_long_double_transpose(dest);
  };
  constexpr static auto add = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_double_add(a, b);
  };
  constexpr static auto sub = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_double_sub(a, b);
  };
  constexpr static auto mul = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_double_mul_elements(a, b);
  };
  constexpr static auto div = [](type *a, const type *b) noexcept {
    return gsl_matrix_long_double_div_elements(a, b);
  };
  constexpr static auto scale = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_long_double_scale(a, b);
  };
  constexpr static auto add_constant = [](type *a, const inst_type b) noexcept {
    return gsl_matrix_long_double_add_constant(a, b);
  };
  constexpr static auto max = [](const type *mat) noexcept {
    return gsl_matrix_long_double_max(mat);
  };
  constexpr static auto min = [](const type *mat) noexcept {
    return gsl_matrix_long_double_min(mat);
  };
  constexpr static auto minmax = [](const type *mat) noexcept {
    inst_type a, b;
    gsl_matrix_long_double_minmax(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto min_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_long_double_min_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto max_index = [](const type *mat) noexcept {
    size_t a, b;
    gsl_matrix_long_double_max_index(mat, &a, &b);
    return std::make_pair(a, b);
  };
  constexpr static auto minmax_index = [](const type *mat) noexcept {
    size_t a, b, c, d;
    gsl_matrix_long_double_minmax_index(mat, &a, &b, &c, &d);
    return std::make_pair(std::make_pair(a, b), std::make_pair(c, d));
  };
  constexpr static auto isnull = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_double_isnull(mat);
  };
  constexpr static auto isneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_double_isneg(mat);
  };
  constexpr static auto ispos = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_double_ispos(mat);
  };
  constexpr static auto isnonneg = [](const type *mat) noexcept -> bool {
    return gsl_matrix_long_double_isnonneg(mat);
  };
  constexpr static auto equal = [](const type *mat,
                                   const type *other) noexcept -> bool {
    return gsl_matrix_long_double_equal(mat, other);
  };
};

template <typename T, template <typename, typename> class TT>
struct is_instantiation_of : std::false_type {};
template <typename T, template <typename, typename> class TT>
struct is_instantiation_of<TT<T, std::default_delete<T>>, TT> : std::true_type {
};
template <typename T, typename D, template <typename, typename> class TT>
struct is_instantiation_of<TT<T, D>, TT> : std::true_type {};
template <typename T, typename D = std::default_delete<T>>
struct is_unique_ptr : is_instantiation_of<T, std::unique_ptr> {};
template <typename T, typename D = std::default_delete<T>>
constexpr bool is_unique_ptr_v = is_unique_ptr<T>::value;

template <typename PtrType> struct Ptr {
  PtrType ptr;
  Ptr() = delete;
  Ptr(const PtrType &_ptr) requires(!is_unique_ptr_v<PtrType>) : ptr(_ptr) {}
  Ptr(PtrType _ptr) requires(is_unique_ptr_v<PtrType>) : ptr(std::move(_ptr)) {}
  Ptr(const Ptr &other) requires(!is_unique_ptr_v<PtrType>) : ptr(other.ptr) {}

  auto get() noexcept {
    if constexpr (is_unique_ptr_v<PtrType>)
      return ptr.get();
    else
      return &ptr;
  }
  auto get() const noexcept {
    if constexpr (is_unique_ptr_v<PtrType>)
      return ptr.get();
    else
      return &ptr;
  }
  auto release() noexcept {
    if constexpr (is_unique_ptr_v<PtrType>)
      return ptr.release();
    else
      return get();
  }
  auto &operator*() noexcept {
    if constexpr (is_unique_ptr_v<PtrType>)
      return *ptr;
    else
      return ptr;
  }
  auto operator->() const noexcept { return get(); }
  constexpr bool operator==(Ptr &other) { return ptr == other.ptr; }
  constexpr bool operator!=(Ptr &other) { return !(*this == other); }
};
} // namespace details
} // namespace gsl
