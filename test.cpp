#include "src/matrix.hpp"
#include <iostream>
#include <type_traits>
using namespace gsl;
int main() {
  matrix<int> a({7, 8, 9, 14, 46, 32, 47, 458, 123}, 3);
  auto b = a.row_view(2);
  b.print(100);
}
