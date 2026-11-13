#pragma once

#include "grad.hpp"
#include "node.hpp"
#include "tape.hpp"
#include "utils.hpp"
#include "var.hpp"

namespace AutoGrad {
    // Arithmetic operations

    /* Addition. */
    template<FloatingPoint S>
    Var<S> operator+(const Var<S>& var1, const Var<S>& var2) {
        if (&var1.tape != &var2.tape) { throw std::invalid_argument("`AutoGrad::Var`s not from the same `AutoGrad::Tape`"); }
        return Var<S>(var1.tape, var1.val + var2.val, var1.tape.push(1.0, var1.idx, 1.0, var2.idx));
    }

    /* Addition. */
    template<FloatingPoint S>
    Var<S> operator+(const Var<S>& var, S scalar) {
        return Var<S>(var.tape, var.val + scalar, var.tape.push(1.0, var.idx));
    }

    /* Addition. */
    template<FloatingPoint S>
    Var<S> operator+(S scalar, const Var<S>& var) {
        return var + scalar;
    }

    /* Subtraction. */
    template<FloatingPoint S>
    Var<S> operator-(const Var<S>& var1, const Var<S>& var2) {
        if (&var1.tape != &var2.tape) { throw std::invalid_argument("`AutoGrad::Var`s not from the same `AutoGrad::Tape`"); }
        return Var<S>(var1.tape, var1.val - var2.val, var1.tape.push(1.0, var1.idx, -1.0, var2.idx));
    }

    /* Subtraction. */
    template<FloatingPoint S>
    Var<S> operator-(const Var<S>& var, S scalar) {
        return Var<S>(var.tape, var.val - scalar, var.tape.push(1.0, var.idx));
    }

    /* Subtraction. */
    template<FloatingPoint S>
    Var<S> operator-(S scalar, const Var<S>& var) {
        return Var<S>(var.tape, scalar - var.val, var.tape.push(-1.0, var.idx));
    }

    /* Multiplication. */
    template<FloatingPoint S>
    Var<S> operator*(const Var<S>& var1, const Var<S>& var2) {
        if (&var1.tape != &var2.tape) { throw std::invalid_argument("`AutoGrad::Var`s not from the same `AutoGrad::Tape`"); }
        return Var<S>(var1.tape, var1.val * var2.val, var1.tape.push(var2.val, var1.idx, var1.val, var2.idx));
    }

    /* Multiplication. */
    template<FloatingPoint S>
    Var<S> operator*(const Var<S>& var, S scalar) {
        return Var<S>(var.tape, var.val * scalar, var.tape.push(scalar, var.idx));
    }

    /* Multiplication. */
    template<FloatingPoint S>
    Var<S> operator*(S scalar, const Var<S>& var) {
        return var * scalar;
    }

    /* Division. */
    template<FloatingPoint S>
    Var<S> operator/(const Var<S>& var1, const Var<S>& var2) {
        if (&var1.tape != &var2.tape) { throw std::invalid_argument("`AutoGrad::Var`s not from the same `AutoGrad::Tape`"); }
        return Var<S>(var1.tape, var1.val / var2.val,
            var1.tape.push(1.0 / var2.val, var1.idx, -var1.val / (var2.val * var2.val), var2.idx));
    }

    /* Division. */
    template<FloatingPoint S>
    Var<S> operator/(const Var<S>& var, S scalar) {
        return Var<S>(var.tape, var.val / scalar, var.tape.push(1.0 / scalar, var.idx));
    }

    /* Division. */
    template<FloatingPoint S>
    Var<S> operator/(S scalar, const Var<S>& var) {
        return Var<S>(var.tape, scalar / var.val, var.tape.push(-scalar / (var.val * var.val), var.idx));
    }

    // Exponentiation and logarithmic functions

    /* Exponentiation (powers). */
    template<FloatingPoint S>
    Var<S> pow(const Var<S>& var1, const Var<S>& var2) {
        if (&var1.tape != &var2.tape) { throw std::invalid_argument("`AutoGrad::Var`s not from the same `AutoGrad::Tape`"); }
        return Var<S>(var1.tape, std::pow(var1.val, var2.val),
            var1.tape.push(var2.val * std::pow(var1.val, var2.val - 1), var1.idx, std::log(var1.val) * std::pow(var1.val, var2.val),
                var2.idx));
    }

    /* Exponentiation (powers). */
    template<FloatingPoint S>
    Var<S> pow(const Var<S>& var, S scalar) {
        return Var<S>(var.tape, std::pow(var.val, scalar), var.tape.push(scalar * std::pow(var.val, scalar - 1), var.idx));
    }

    /* Exponentiation (powers). */
    template<FloatingPoint S>
    Var<S> pow(S scalar, const Var<S>& var) {
        return Var<S>(var.tape, std::pow(scalar, var.val), var.tape.push(std::log(scalar) * std::pow(scalar, var.val), var.idx));
    }

    /* Square root. */
    template<FloatingPoint S>
    Var<S> sqrt(const Var<S>& var) {
        return Var<S>(var.tape, std::sqrt(var.val), var.tape.push(0.5 / std::sqrt(var.val), var.idx));
    }

    /* Cube root. */
    template<FloatingPoint S>
    Var<S> cbrt(const Var<S>& var) {
        return Var<S>(var.tape, std::cbrt(var.val), var.tape.push(1.0 / (3.0 * std::cbrt(var.val) * std::cbrt(var.val)), var.idx));
    }

    /* Exponential function. */
    template<FloatingPoint S>
    Var<S> exp(const Var<S>& var) {
        return Var<S>(var.tape, std::exp(var.val), var.tape.push(std::exp(var.val), var.idx));
    }

    /* Base-2 exponential function. */
    template<FloatingPoint S>
    Var<S> exp2(const Var<S>& var) {
        return Var<S>(var.tape, std::exp2(var.val), var.tape.push(std::exp2(var.val) * std::log(2), var.idx));
    }

    /* Natural logarithm. */
    template<FloatingPoint S>
    Var<S> log(const Var<S>& var) {
        return Var<S>(var.tape, std::log(var.val), var.tape.push(1.0 / var.val, var.idx));
    }

    /* Logarithm with a specified base. */
    template<FloatingPoint S>
    Var<S> log(const Var<S>& var, const Var<S>& base) {
        if (&var.tape != &base.tape) { throw std::invalid_argument("`AutoGrad::Var`s not from the same `AutoGrad::Tape`"); }
        return Var<S>(var.tape, std::log(var.val) / std::log(base.val),
            var.tape.push(1.0 / (var.val * std::log(base.val)), var.idx,
                -std::log(var.val) / (base.val * std::log(base.val) * std::log(base.val)), base.idx));
    }

    /* Logarithm with a specified base. */
    template<FloatingPoint S>
    Var<S> log(const Var<S>& var, S base) {
        return Var<S>(var.tape, std::log(var.val) / std::log(base), var.tape.push(1.0 / (var.val * std::log(base)), var.idx));
    }

    /* Logarithm with a specified base. */
    template<FloatingPoint S>
    Var<S> log(S scalar, const Var<S>& base) {
        return Var<S>(base.tape, std::log(scalar) / std::log(base.val),
            base.tape.push(-std::log(scalar) / (base.val * std::log(base.val) * std::log(base.val)), base.idx));
    }

    /* Natural logarithm. */
    template<FloatingPoint S>
    Var<S> ln(const Var<S>& var) {
        return log(var);
    }

    /* Base-2 logarithm. */
    template<FloatingPoint S>
    Var<S> log2(const Var<S>& var) {
        return Var<S>(var.tape, std::log2(var.val), var.tape.push(1.0 / (var.val * std::log(2)), var.idx));
    }

    /* Base-10 logarithm. */
    template<FloatingPoint S>
    Var<S> log10(const Var<S>& var) {
        return Var<S>(var.tape, std::log10(var.val), var.tape.push(1.0 / (var.val * std::log(10)), var.idx));
    }

    // Trigonometric functions

    /* Sine. */
    template<FloatingPoint S>
    Var<S> sin(const Var<S>& var) {
        return Var<S>(var.tape, std::sin(var.val), var.tape.push(std::cos(var.val), var.idx));
    }

    /* Cosine. */
    template<FloatingPoint S>
    Var<S> cos(const Var<S>& var) {
        return Var<S>(var.tape, std::cos(var.val), var.tape.push(-std::sin(var.val), var.idx));
    }

    /* Tangent. */
    template<FloatingPoint S>
    Var<S> tan(const Var<S>& var) {
        return Var<S>(var.tape, std::tan(var.val), var.tape.push(1.0 / (std::cos(var.val) * std::cos(var.val)), var.idx));
    }

    /* Secant. */
    template<FloatingPoint S>
    Var<S> sec(const Var<S>& var) {
        return Var<S>(var.tape, 1.0 / std::cos(var.val), var.tape.push(std::tan(var.val) / std::cos(var.val), var.idx));
    }

    /* Cosecant. */
    template<FloatingPoint S>
    Var<S> csc(const Var<S>& var) {
        return Var<S>(var.tape, 1.0 / std::sin(var.val),
            var.tape.push(-std::cos(var.val) / (std::sin(var.val) * std::sin(var.val)), var.idx));
    }

    /* Cotangent. */
    template<FloatingPoint S>
    Var<S> cot(const Var<S>& var) {
        return Var<S>(var.tape, 1.0 / std::tan(var.val), var.tape.push(-1.0 / (std::sin(var.val) * std::sin(var.val)), var.idx));
    }

    /* Inverse sine. */
    template<FloatingPoint S>
    Var<S> arcsin(const Var<S>& var) {
        return Var<S>(var.tape, std::asin(var.val), var.tape.push(1.0 / std::sqrt(1.0 - var.val * var.val), var.idx));
    }

    /* Inverse cosine. */
    template<FloatingPoint S>
    Var<S> arccos(const Var<S>& var) {
        return Var<S>(var.tape, std::acos(var.val), var.tape.push(-1.0 / std::sqrt(1.0 - var.val * var.val), var.idx));
    }

    /* Inverse tangent. */
    template<FloatingPoint S>
    Var<S> arctan(const Var<S>& var) {
        return Var<S>(var.tape, std::atan(var.val), var.tape.push(1.0 / (1.0 + var.val * var.val), var.idx));
    }

    /* Inverse secant. */
    template<FloatingPoint S>
    Var<S> arcsec(const Var<S>& var) {
        return Var<S>(var.tape, std::acos(1.0 / var.val),
            var.tape.push(-1.0 / (std::abs(var.val) * std::sqrt(var.val * var.val - 1.0)), var.idx));
    }

    /* Inverse cosecant. */
    template<FloatingPoint S>
    Var<S> arccsc(const Var<S>& var) {
        return Var<S>(var.tape, std::asin(1.0 / var.val),
            var.tape.push(-1.0 / (std::abs(var.val) * std::sqrt(var.val * var.val - 1.0)), var.idx));
    }

    /* Inverse cotangent. */
    template<FloatingPoint S>
    Var<S> arccot(const Var<S>& var) {
        return Var<S>(var.tape, (var.val >= 0) ? (std::atan(1.0 / var.val)) : (std::atan(1.0 / var.val) + std::numbers::pi_v<S>),
            var.tape.push(-1.0 / (1.0 + var.val * var.val), var.idx));
    }

    // Hyperbolic trigonometric functions

    /* Hyperbolic sine. */
    template<FloatingPoint S>
    Var<S> sinh(const Var<S>& var) {
        return Var<S>(var.tape, std::sinh(var.val), var.tape.push(std::cosh(var.val), var.idx));
    }

    /* Hyperbolic cosine. */
    template<FloatingPoint S>
    Var<S> cosh(const Var<S>& var) {
        return Var<S>(var.tape, std::cosh(var.val), var.tape.push(std::sinh(var.val), var.idx));
    }

    /* Hyperbolic tangent. */
    template<FloatingPoint S>
    Var<S> tanh(const Var<S>& var) {
        return Var<S>(var.tape, std::tanh(var.val), var.tape.push(1.0 - std::tanh(var.val) * std::tanh(var.val), var.idx));
    }

    /* Hyperbolic secant. */
    template<FloatingPoint S>
    Var<S> sech(const Var<S>& var) {
        return Var<S>(var.tape, 1.0 / std::cosh(var.val), var.tape.push(-std::tanh(var.val) / std::cosh(var.val), var.idx));
    }

    /* Hyperbolic cosecant. */
    template<FloatingPoint S>
    Var<S> csch(const Var<S>& var) {
        return Var<S>(var.tape, 1.0 / std::sinh(var.val),
            var.tape.push(-std::cosh(var.val) / (std::sinh(var.val) * std::sinh(var.val)), var.idx));
    }

    /* Hyperbolic cotangent. */
    template<FloatingPoint S>
    Var<S> coth(const Var<S>& var) {
        return Var<S>(var.tape, 1.0 / std::tanh(var.val), var.tape.push(-1.0 / (std::sinh(var.val) * std::sinh(var.val)), var.idx));
    }

    /* Inverse hyperbolic sine. */
    template<FloatingPoint S>
    Var<S> arsinh(const Var<S>& var) {
        return Var<S>(var.tape, std::asinh(var.val), var.tape.push(1.0 / std::sqrt(var.val * var.val + 1.0), var.idx));
    }

    /* Inverse hyperbolic cosine. */
    template<FloatingPoint S>
    Var<S> arcosh(const Var<S>& var) {
        return Var<S>(var.tape, std::acosh(var.val), var.tape.push(1.0 / std::sqrt(var.val * var.val - 1.0), var.idx));
    }

    /* Inverse hyperbolic tangent. */
    template<FloatingPoint S>
    Var<S> artanh(const Var<S>& var) {
        return Var<S>(var.tape, std::atanh(var.val), var.tape.push(1.0 / (1.0 - var.val * var.val), var.idx));
    }

    /* Inverse hyperbolic secant. */
    template<FloatingPoint S>
    Var<S> arsech(const Var<S>& var) {
        return Var<S>(var.tape, std::acosh(1.0 / var.val),
            var.tape.push(-1.0 / (std::abs(var.val) * std::sqrt(1.0 - var.val * var.val)), var.idx));
    }

    /* Inverse hyperbolic cosecant. */
    template<FloatingPoint S>
    Var<S> arcsch(const Var<S>& var) {
        return Var<S>(var.tape, std::asinh(1.0 / var.val),
            var.tape.push(-1.0 / (std::abs(var.val) * std::sqrt(1.0 + var.val * var.val)), var.idx));
    }

    /* Inverse hyperbolic cotangent. */
    template<FloatingPoint S>
    Var<S> arcoth(const Var<S>& var) {
        return Var<S>(var.tape, std::atanh(1.0 / var.val), var.tape.push(1.0 / (1.0 - var.val * var.val), var.idx));
    }

    /* Absolute value. */
    template<FloatingPoint S>
    Var<S> abs(const Var<S>& var) {
        return Var<S>(var.tape, std::abs(var.val), var.tape.push(std::abs(var.val) / var.val, var.idx));
    }
}
