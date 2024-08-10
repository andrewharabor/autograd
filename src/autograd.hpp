
#ifndef AUTOGRAD_AUTOGRAD_HPP
#define AUTOGRAD_AUTOGRAD_HPP


#include "gradient.hpp"
#include "node.hpp"
#include "tape.hpp"
#include "utils.hpp"
#include "variable.hpp"

namespace AutoGrad {

  // Arithmetic operations

  /* Addition. */
  template<FloatingPoint S>
  Variable<S> operator+(const Variable<S> &variable1, const Variable<S> &variable2) {
    if (&variable1.tape != &variable2.tape) {
      throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
    }
    return Variable<S>(variable1.tape, variable1.val + variable2.val, variable1.tape.push_back(1.0, variable1.index, 1.0, variable2.index));
  }

  /* Addition. */
  template<FloatingPoint S>
  Variable<S> operator+(const Variable<S> &variable, S scalar) {
    return Variable<S>(variable.tape, variable.val + scalar, variable.tape.push_back(1.0, variable.index));
  }

  /* Addition. */
  template<FloatingPoint S>
  Variable<S> operator+(S scalar, const Variable<S> &variable) {
    return variable + scalar;
  }

  /* Subtraction. */
  template<FloatingPoint S>
  Variable<S> operator-(const Variable<S> &variable1, const Variable<S> &variable2) {
    if (&variable1.tape != &variable2.tape) {
      throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
    }
    return Variable<S>(variable1.tape, variable1.val - variable2.val, variable1.tape.push_back(1.0, variable1.index, -1.0, variable2.index));
  }

  /* Subtraction. */
  template<FloatingPoint S>
  Variable<S> operator-(const Variable<S> &variable, S scalar) {
    return Variable<S>(variable.tape, variable.val - scalar, variable.tape.push_back(1.0, variable.index));
  }

  /* Subtraction. */
  template<FloatingPoint S>
  Variable<S> operator-(S scalar, const Variable<S> &variable) {
    return Variable<S>(variable.tape, scalar - variable.val, variable.tape.push_back(-1.0, variable.index));
  }

  /* Multiplication. */
  template<FloatingPoint S>
  Variable<S> operator*(const Variable<S> &variable1, const Variable<S> &variable2) {
    if (&variable1.tape != &variable2.tape) {
      throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
    }
    return Variable<S>(variable1.tape, variable1.val * variable2.val, variable1.tape.push_back(variable2.val, variable1.index, variable1.val, variable2.index));
  }

  /* Multiplication. */
  template<FloatingPoint S>
  Variable<S> operator*(const Variable<S> &variable, S scalar) {
    return Variable<S>(variable.tape, variable.val * scalar, variable.tape.push_back(scalar, variable.index));
  }

  /* Multiplication. */
  template<FloatingPoint S>
  Variable<S> operator*(S scalar, const Variable<S> &variable) {
    return variable * scalar;
  }

  /* Division. */
  template<FloatingPoint S>
  Variable<S> operator/(const Variable<S> &variable1, const Variable<S> &variable2) {
    if (&variable1.tape != &variable2.tape) {
      throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
    }
    return Variable<S>(variable1.tape, variable1.val / variable2.val, variable1.tape.push_back(1.0 / variable2.val, variable1.index, -variable1.val / (variable2.val * variable2.val), variable2.index));
  }

  /* Division. */
  template<FloatingPoint S>
  Variable<S> operator/(const Variable<S> &variable, S scalar) {
    return Variable<S>(variable.tape, variable.val / scalar, variable.tape.push_back(1.0 / scalar, variable.index));
  }

  /* Division. */
  template<FloatingPoint S>
  Variable<S> operator/(S scalar, const Variable<S> &variable) {
    return Variable<S>(variable.tape, scalar / variable.val, variable.tape.push_back(-scalar / (variable.val * variable.val), variable.index));
  }

  // Exponentiation and logarithmic functions

  /* Exponentiation (powers). */
  template<FloatingPoint S>
  Variable<S> pow(const Variable<S> &variable1, const Variable<S> &variable2) {
    if (&variable1.tape != &variable2.tape) {
      throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
    }
    return Variable<S>(variable1.tape, std::pow(variable1.val, variable2.val), variable1.tape.push_back(variable2.val * std::pow(variable1.val, variable2.val - 1), variable1.index, std::log(variable1.val) * std::pow(variable1.val, variable2.val), variable2.index));
  }

  /* Exponentiation (powers). */
  template<FloatingPoint S>
  Variable<S> pow(const Variable<S> &variable, S scalar) {
    return Variable<S>(variable.tape, std::pow(variable.val, scalar), variable.tape.push_back(scalar * std::pow(variable.val, scalar - 1), variable.index));
  }

  /* Exponentiation (powers). */
  template<FloatingPoint S>
  Variable<S> pow(S scalar, const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::pow(scalar, variable.val), variable.tape.push_back(std::log(scalar) * std::pow(scalar, variable.val), variable.index));
  }

  /* Square root. */
  template<FloatingPoint S>
  Variable<S> sqrt(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::sqrt(variable.val), variable.tape.push_back(0.5 / std::sqrt(variable.val), variable.index));
  }

  /* Cube root. */
  template<FloatingPoint S>
  Variable<S> cbrt(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::cbrt(variable.val), variable.tape.push_back(1.0 / (3.0 * std::cbrt(variable.val) * std::cbrt(variable.val)), variable.index));
  }

  /* Exponential function. */
  template<FloatingPoint S>
  Variable<S> exp(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::exp(variable.val), variable.tape.push_back(std::exp(variable.val), variable.index));
  }

  /* Base-2 exponential function. */
  template<FloatingPoint S>
  Variable<S> exp2(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::exp2(variable.val), variable.tape.push_back(std::exp2(variable.val) * std::log(2), variable.index));
  }

  /* Natural logarithm. */
  template<FloatingPoint S>
  Variable<S> log(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::log(variable.val), variable.tape.push_back(1.0 / variable.val, variable.index));
  }

  /* Logarithm with a specified base. */
  template<FloatingPoint S>
  Variable<S> log(const Variable<S> &variable, const Variable<S> &base) {
    if (&variable.tape != &base.tape) {
      throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
    }
    return Variable<S>(variable.tape, std::log(variable.val) / std::log(base.val), variable.tape.push_back(1.0 / (variable.val * std::log(base.val)), variable.index, -std::log(variable.val) / (base.val * std::log(base.val) * std::log(base.val)), base.index));
  }

  /* Logarithm with a specified base. */
  template<FloatingPoint S>
  Variable<S> log(const Variable<S> &variable, S base) {
    return Variable<S>(variable.tape, std::log(variable.val) / std::log(base), variable.tape.push_back(1.0 / (variable.val * std::log(base)), variable.index));
  }

  /* Logarithm with a specified base. */
  template<FloatingPoint S>
  Variable<S> log(S scalar, const Variable<S> &base) {
    return Variable<S>(base.tape, std::log(scalar) / std::log(base.val), base.tape.push_back(-std::log(scalar) / (base.val * std::log(base.val) * std::log(base.val)), base.index));
  }

  /* Natural logarithm. */
  template<FloatingPoint S>
  Variable<S> ln(const Variable<S> &variable) {
    return log(variable);
  }

  /* Base-2 logarithm. */
  template<FloatingPoint S>
  Variable<S> log2(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::log2(variable.val), variable.tape.push_back(1.0 / (variable.val * std::log(2)), variable.index));
  }

  /* Base-10 logarithm. */
  template<FloatingPoint S>
  Variable<S> log10(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::log10(variable.val), variable.tape.push_back(1.0 / (variable.val * std::log(10)), variable.index));
  }

  // Trigonometric functions

  /* Sine. */
  template<FloatingPoint S>
  Variable<S> sin(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::sin(variable.val), variable.tape.push_back(std::cos(variable.val), variable.index));
  }

  /* Cosine. */
  template<FloatingPoint S>
  Variable<S> cos(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::cos(variable.val), variable.tape.push_back(-std::sin(variable.val), variable.index));
  }

  /* Tangent. */
  template<FloatingPoint S>
  Variable<S> tan(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::tan(variable.val), variable.tape.push_back(1.0 / (std::cos(variable.val) * std::cos(variable.val)), variable.index));
  }

  /* Secant. */
  template<FloatingPoint S>
  Variable<S> sec(const Variable<S> &variable) {
    return Variable<S>(variable.tape, 1.0 / std::cos(variable.val), variable.tape.push_back(std::tan(variable.val) / std::cos(variable.val), variable.index));
  }

  /* Cosecant. */
  template<FloatingPoint S>
  Variable<S> csc(const Variable<S> &variable) {
    return Variable<S>(variable.tape, 1.0 / std::sin(variable.val), variable.tape.push_back(-std::cos(variable.val) / (std::sin(variable.val) * std::sin(variable.val)), variable.index));
  }

  /* Cotangent. */
  template<FloatingPoint S>
  Variable<S> cot(const Variable<S> &variable) {
    return Variable<S>(variable.tape, 1.0 / std::tan(variable.val), variable.tape.push_back(-1.0 / (std::sin(variable.val) * std::sin(variable.val)), variable.index));
  }

  /* Inverse sine. */
  template<FloatingPoint S>
  Variable<S> arcsin(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::asin(variable.val), variable.tape.push_back(1.0 / std::sqrt(1.0 - variable.val * variable.val), variable.index));
  }

  /* Inverse cosine. */
  template<FloatingPoint S>
  Variable<S> arccos(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::acos(variable.val), variable.tape.push_back(-1.0 / std::sqrt(1.0 - variable.val * variable.val), variable.index));
  }

  /* Inverse tangent. */
  template<FloatingPoint S>
  Variable<S> arctan(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::atan(variable.val), variable.tape.push_back(1.0 / (1.0 + variable.val * variable.val), variable.index));
  }

  /* Inverse secant. */
  template<FloatingPoint S>
  Variable<S> arcsec(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::acos(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(variable.val * variable.val - 1.0)), variable.index));
  }

  /* Inverse cosecant. */
  template<FloatingPoint S>
  Variable<S> arccsc(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::asin(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(variable.val * variable.val - 1.0)), variable.index));
  }

  /* Inverse cotangent. */
  template<FloatingPoint S>
  Variable<S> arccot(const Variable<S> &variable) {
    return Variable<S>(variable.tape, (variable.val >= 0) ? (std::atan(1.0 / variable.val)) : (std::atan(1.0 / variable.val) + std::numbers::pi_v<S>), variable.tape.push_back(-1.0 / (1.0 + variable.val * variable.val), variable.index));
  }

  // Hyperbolic trigonometric functions

  /* Hyperbolic sine. */
  template<FloatingPoint S>
  Variable<S> sinh(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::sinh(variable.val), variable.tape.push_back(std::cosh(variable.val), variable.index));
  }

  /* Hyperbolic cosine. */
  template<FloatingPoint S>
  Variable<S> cosh(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::cosh(variable.val), variable.tape.push_back(std::sinh(variable.val), variable.index));
  }

  /* Hyperbolic tangent. */
  template<FloatingPoint S>
  Variable<S> tanh(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::tanh(variable.val), variable.tape.push_back(1.0 - std::tanh(variable.val) * std::tanh(variable.val), variable.index));
  }

  /* Hyperbolic secant. */
  template<FloatingPoint S>
  Variable<S> sech(const Variable<S> &variable) {
    return Variable<S>(variable.tape, 1.0 / std::cosh(variable.val), variable.tape.push_back(-std::tanh(variable.val) / std::cosh(variable.val), variable.index));
  }

  /* Hyperbolic cosecant. */
  template<FloatingPoint S>
  Variable<S> csch(const Variable<S> &variable) {
    return Variable<S>(variable.tape, 1.0 / std::sinh(variable.val), variable.tape.push_back(-std::cosh(variable.val) / (std::sinh(variable.val) * std::sinh(variable.val)), variable.index));
  }

  /* Hyperbolic cotangent. */
  template<FloatingPoint S>
  Variable<S> coth(const Variable<S> &variable) {
    return Variable<S>(variable.tape, 1.0 / std::tanh(variable.val), variable.tape.push_back(-1.0 / (std::sinh(variable.val) * std::sinh(variable.val)), variable.index));
  }

  /* Inverse hyperbolic sine. */
  template<FloatingPoint S>
  Variable<S> arsinh(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::asinh(variable.val), variable.tape.push_back(1.0 / std::sqrt(variable.val * variable.val + 1.0), variable.index));
  }

  /* Inverse hyperbolic cosine. */
  template<FloatingPoint S>
  Variable<S> arcosh(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::acosh(variable.val), variable.tape.push_back(1.0 / std::sqrt(variable.val * variable.val - 1.0), variable.index));
  }

  /* Inverse hyperbolic tangent. */
  template<FloatingPoint S>
  Variable<S> artanh(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::atanh(variable.val), variable.tape.push_back(1.0 / (1.0 - variable.val * variable.val), variable.index));
  }

  /* Inverse hyperbolic secant. */
  template<FloatingPoint S>
  Variable<S> arsech(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::acosh(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(1.0 - variable.val * variable.val)), variable.index));
  }

  /* Inverse hyperbolic cosecant. */
  template<FloatingPoint S>
  Variable<S> arcsch(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::asinh(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(1.0 + variable.val * variable.val)), variable.index));
  }

  /* Inverse hyperbolic cotangent. */
  template<FloatingPoint S>
  Variable<S> arcoth(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::atanh(1.0 / variable.val), variable.tape.push_back(1.0 / (1.0 - variable.val * variable.val), variable.index));
  }

  /* Absolute value. */
  template<FloatingPoint S>
  Variable<S> abs(const Variable<S> &variable) {
    return Variable<S>(variable.tape, std::abs(variable.val), variable.tape.push_back(std::abs(variable.val) / variable.val, variable.index));
  }
}


#endif // AUTOGRAD_AUTOGRAD_HPP
