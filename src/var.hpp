#pragma once

#include "grad.hpp"
#include "node.hpp"
#include "tape.hpp"
#include "utils.hpp"

namespace AutoGrad {
    template<FloatingPoint Scalar>
    class Tape;  // Forward declaration

    template<FloatingPoint Scalar>
    class Grad;  // Forward declaration

    /* A floating-point variable type that uses information about operations performed on it in order to offer gradient
    computation. */
    template<FloatingPoint Scalar>
    class Var {
        friend class Tape<Scalar>;
        friend class Grad<Scalar>;

        // Comparison operators

        /* Equality.
        NOTE: this directly compares two floating-point values using `==` and is therefore unsafe. */
        template<FloatingPoint S>
        friend bool operator==(const Var<S>& variable1, const Var<S>& variable2) {
            return variable1.val == variable2.val;
        }

        /* Inequality.
        NOTE: this directly compares two floating-point values using `!=` and is therefore unsafe. */
        template<FloatingPoint S>
        friend bool operator!=(const Var<S>& variable1, const Var<S>& variable2) {
            return variable1.val != variable2.val;
        }

        /* Greater than. */
        template<FloatingPoint S>
        friend bool operator>(const Var<S>& variable1, const Var<S>& variable2) {
            return variable1.val > variable2.val;
        }

        /* Less than. */
        template<FloatingPoint S>
        friend bool operator<(const Var<S>& variable1, const Var<S>& variable2) {
            return variable1.val < variable2.val;
        }

        /* Greater than or equal to. */
        template<FloatingPoint S>
        friend bool operator>=(const Var<S>& variable1, const Var<S>& variable2) {
            return variable1.val >= variable2.val;
        }

        /* Less than or equal to. */
        template<FloatingPoint S>
        friend bool operator<=(const Var<S>& variable1, const Var<S>& variable2) {
            return variable1.val <= variable2.val;
        }

        // A bunch of arithmetic operations and elementary mathematical functions that have to be declared as friends so
        // that they can access private members and methods.
        // I know it's ugly but I don't think there is another option aside from making class internals public.

        // Arithmetic operations

        template<FloatingPoint S>
        friend Var<S> operator+(const Var<S>& variable1, const Var<S>& variable2);

        template<FloatingPoint S>
        friend Var<S> operator+(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator+(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> operator-(const Var<S>& variable1, const Var<S>& variable2);

        template<FloatingPoint S>
        friend Var<S> operator-(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator-(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> operator*(const Var<S>& variable1, const Var<S>& variable2);

        template<FloatingPoint S>
        friend Var<S> operator*(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator*(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> operator/(const Var<S>& variable1, const Var<S>& variable2);

        template<FloatingPoint S>
        friend Var<S> operator/(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator/(S scalar, const Var<S>& var);

        // Exponential and logarithmic functions

        template<FloatingPoint S>
        friend Var<S> pow(const Var<S>& variable1, const Var<S>& variable2);

        template<FloatingPoint S>
        friend Var<S> pow(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> pow(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> sqrt(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> cbrt(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> exp(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> exp2(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> log(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> log(const Var<S>& var, const Var<S>& base);

        template<FloatingPoint S>
        friend Var<S> log(const Var<S>& var, S base);

        template<FloatingPoint S>
        friend Var<S> log(S scalar, const Var<S>& base);

        template<FloatingPoint S>
        friend Var<S> ln(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> log2(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> log10(const Var<S>& var);

        // Trigonometric functions

        template<FloatingPoint S>
        friend Var<S> sin(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> cos(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> tan(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> sec(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> csc(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> cot(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arcsin(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arccos(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arctan(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arcsec(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arccsc(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arccot(const Var<S>& var);

        // Hyperbolic trigonometric functions

        template<FloatingPoint S>
        friend Var<S> sinh(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> cosh(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> tanh(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> sech(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> csch(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> coth(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arsinh(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arcosh(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> artanh(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arsech(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arcsch(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> arcoth(const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> abs(const Var<S>& var);

    public:
        /* Construct a new variable object by copying the value of the given one. */
        Var(const Var<Scalar>& var) noexcept : tape(var.tape), val{var.val} {  // Copy constructor
            idx = tape.push(1.0, var.idx);
        }

        /* Construct a new variable object by moving the given one. */
        Var(Var<Scalar>&& var) noexcept = default;  // Move constructor

        // Assignment operators

        /* Reassign a variable object by copying the value of the given one. */
        Var<Scalar>& operator=(const Var<Scalar>& var) {
            if (this != &var) {
                if (&tape != &var.tape) { throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`"); }
                val = var.val;
                idx = tape.push(1.0, var.idx);
            }
            return *this;
        }

        /* Reassign a variable object by moving the given one. */
        Var<Scalar>& operator=(Var<Scalar>&& var) {
            if (&tape != &var.tape) { throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`"); }
            val = var.val;
            idx = var.idx;
            return *this;
        }

        /* Reassign a variable object using a scalar. */
        Var<Scalar>& operator=(Scalar scalar) {
            val = scalar;
            idx = tape.push();
            return *this;
        }

        /* Addition assignment. */
        Var<Scalar>& operator+=(const Var<Scalar>& var) {
            *this = *this + var;
            return *this;
        }

        /* Addition assignment. */
        Var<Scalar>& operator+=(Scalar scalar) {
            *this = *this + scalar;
            return *this;
        }

        /* Subtraction assignment. */
        Var<Scalar>& operator-=(const Var<Scalar>& var) {
            *this = *this - var;
            return *this;
        }

        /* Subtraction assignment. */
        Var<Scalar>& operator-=(Scalar scalar) {
            *this = *this - scalar;
            return *this;
        }

        /* Multiplication assignment. */
        Var<Scalar>& operator*=(const Var<Scalar>& var) {
            *this = *this * var;
            return *this;
        }

        /* Multiplication assignment. */
        Var<Scalar>& operator*=(Scalar scalar) {
            *this = *this * scalar;
            return *this;
        }

        /* Division assignment. */
        Var<Scalar>& operator/=(const Var<Scalar>& var) {
            *this = *this / var;
            return *this;
        }

        /* Division assignment. */
        Var<Scalar>& operator/=(Scalar scalar) {
            *this = *this / scalar;
            return *this;
        }

        /* Identity. */
        Var<Scalar> operator+() const { return Var<Scalar>(tape, val, tape.push(1.0, idx)); }

        /* Negation. */
        Var<Scalar> operator-() const { return Var<Scalar>(tape, -val, tape.push(-1.0, idx)); }

        /* Retrive the actual numerical value. */
        Scalar value() const { return val; }

        /* Compute the gradient: the partial derivatives with respect to all input variables. */
        Grad<Scalar> grad() const {
            size_t size = tape.nodes.size();
            std::vector<Scalar> grads(size, 0.0);
            grads[idx] = 1.0;
            for (size_t i = size; i-- > 0;) {
                Node<Scalar>& node = tape.nodes[i];
                grads[node.deps.first] += node.weights.first * grads[i];
                grads[node.deps.second] += node.weights.second * grads[i];
            }
            return Grad<Scalar>(tape, grads);
        }

    private:
        Tape<Scalar>& tape;  // Tape that the variable was created on.
        Scalar val;          //  Actual numerical value.
        size_t idx;          // Index in the computational graph held by the tape.

        /* Construct a variable object for a particular tape given a value and an index. */
        Var(Tape<Scalar>& tape_, Scalar val_, size_t idx_) noexcept : tape(tape_), val{val_}, idx{idx_} {}  // Constructor
    };
}
