#pragma once

#include "node.hpp"
#include "utils.hpp"
#include "var.hpp"

namespace AutoGrad {
    template<FloatingPoint Scalar>
    class Var;  // Forward declaration

    template<FloatingPoint Scalar>
    class Grad;  // Forward declaration

    /* A gradient tape that stores a computational graph recording mathematical operations perfomed on variables in order
    to compute derivatives. */
    template<FloatingPoint Scalar>
    class Tape {
        friend class Var<Scalar>;
        friend class Grad<Scalar>;

        // A bunch of arithmetic operations and elementary mathematical functions that have to be declared as friends so
        // that they can access private members and methods.
        // I know it's ugly but I don't think there is another option aside from making class internals public.

        // Arithmetic operations

        template<FloatingPoint S>
        friend Var<S> operator+(const Var<S>& var1, const Var<S>& var2);

        template<FloatingPoint S>
        friend Var<S> operator+(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator+(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> operator-(const Var<S>& var1, const Var<S>& var2);

        template<FloatingPoint S>
        friend Var<S> operator-(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator-(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> operator*(const Var<S>& var1, const Var<S>& var2);

        template<FloatingPoint S>
        friend Var<S> operator*(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator*(S scalar, const Var<S>& var);

        template<FloatingPoint S>
        friend Var<S> operator/(const Var<S>& var1, const Var<S>& var2);

        template<FloatingPoint S>
        friend Var<S> operator/(const Var<S>& var, S scalar);

        template<FloatingPoint S>
        friend Var<S> operator/(S scalar, const Var<S>& var);

        // Exponential and logarithmic functions

        template<FloatingPoint S>
        friend Var<S> pow(const Var<S>& var1, const Var<S>& var2);

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
        /* Construct a new tape object. */
        Tape() noexcept = default;  // Default constructor

        // Disallow copy semantics
        // Each tape has variables bound to that specific reference so copying tapes would lead to weird behavior.

        Tape(const Tape<Scalar>& tape) noexcept = delete;                     // Copy constructor
        Tape<Scalar>& operator=(const Tape<Scalar>& tape) noexcept = delete;  // Copy assignment operator

        // But allow move semantics

        /* Construct a new tape object by moving the given one. */
        Tape(Tape<Scalar>&& tape) noexcept = default;  // Move constructor

        /* Assign a new tape by moving the given one. */
        Tape<Scalar>& operator=(Tape<Scalar>&& tape) noexcept = default;  // Move assignment operator

        /* Instantiate a new variable object (that is permanently bound to the tape) as part of the computational graph. */
        Var<Scalar> var(Scalar value) { return Var<Scalar>(*this, value, push()); }

    private:
        std::vector<Node<Scalar>> nodes;  // Internal representation of the computational graph.

        /* Push an empty node to the computational graph that represents a new variable. */
        size_t push() {
            size_t size = nodes.size();
            nodes.push_back(Node<Scalar>(std::make_pair(0.0, 0.0), std::make_pair(size, size)));
            return size;
        }

        /* Push a node to the computational graph that stores the result of a unary operation. */
        size_t push(Scalar weight, size_t dep) {
            size_t size = nodes.size();
            nodes.push_back(Node<Scalar>(std::make_pair(weight, 0.0), std::make_pair(dep, size)));
            return size;
        }

        /* Push a node to the computational graph that stores the result of a binary operation. */
        size_t push(Scalar weight1, size_t dep1, Scalar weight2, size_t dep2) {
            size_t size = nodes.size();
            nodes.push_back(Node<Scalar>(std::make_pair(weight1, weight2), std::make_pair(dep1, dep2)));
            return size;
        }
    };
}
