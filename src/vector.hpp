#pragma once
#include "vector_impl.hpp"
namespace gsl {
template <typename T> using vector = details::vector_impl<T, false>;
template <typename T> using vector_view = details::vector_impl<T, true>;
} // namespace gsl
