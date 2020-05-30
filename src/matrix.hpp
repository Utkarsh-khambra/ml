#pragma once
#include "matrix_impl.hpp"
namespace gsl {
template <typename T>
requires(std::is_arithmetic_v<T>) using matrix = details::matrix_impl<T, false>;
template <typename T>
requires(std::is_arithmetic_v<T>) using matrix_view =
    details::matrix_impl<T, true>;
} // namespace gsl
