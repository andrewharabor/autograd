
#ifndef AUTOGRAD_UTILS_HPP
#define AUTOGRAD_UTILS_HPP


#include <cmath>
#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

/* Contains all templated classes and functions from the AutoGrad library. */
namespace AutoGrad {

  /* Determines if a type is a floating-point type (i.e., `float`, `double`, `long double`, or the fixed-width types
  found in the standard header `<stdfloat>` for C++23). */
  template<typename T>
  concept FloatingPoint = std::floating_point<T>;
}


#endif // AUTOGRAD_UTILS_HPP
