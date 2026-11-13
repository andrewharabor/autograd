#pragma once

#include <cmath>
#include <concepts>
#include <cstddef>
#include <numbers>
#include <stdexcept>
#include <utility>
#include <vector>

/* Contains all templated classes and functions from the AutoGrad library. */
namespace AutoGrad {
    /* Determines if a type is a floating-point type (i.e., `float`, `double`, `long double`). */
    template<typename T>
    concept FloatingPoint = std::floating_point<T>;
}
