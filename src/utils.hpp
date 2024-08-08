
#ifndef AUTOGRAD_UTILS_HPP
#define AUTOGRAD_UTILS_HPP


#include <cmath>
#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <numbers>
#include <utility>
#include <vector>

namespace AutoGrad {
  template<typename T>
  concept FloatingPoint = std::floating_point<T>;
}


#endif // AUTOGRAD_UTILS_HPP
