#include "src/matrix_impl.hpp"
#include <iostream>
#include <type_traits>
using namespace gsl::details;
int main() {
  matrix_impl<int, false> a(
      {78, 41, 25, 346, 478, 145, 478, 12, -78, 12, 78, 13, 24, 45, 78, 45}, 4);
  a.print();
  a = 2 * a;
  a.print();
}
