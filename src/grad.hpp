#pragma once

#include "utils.hpp"
#include "var.hpp"

namespace AutoGrad {
    template<FloatingPoint Scalar>
    class Var;  // Forward declaration

    /* Contains information about the gradient of a particular tape: the partial derivatives of a single output variable
    with respect to all input variables. */
    template<FloatingPoint Scalar>
    class Grad {
        friend class Var<Scalar>;

    public:
        /* Retrieve the partial derivative with respect to the given variable. */
        Scalar wrt(const Var<Scalar>& var) const {
            if (&tape != &var.tape) {
                throw std::invalid_argument("`AutoGrad::Var` not from the same `AutoGrad::Tape` as `AutoGrad::Grad`");
            }
            return grads[var.idx];
        }

    private:
        Tape<Scalar>& tape;         // Tape that the gradient was computed on.
        std::vector<Scalar> grads;  // Partial derivatives w.r.t each input variable.

        /* Construct a gradient object for a particular tape given the gradients. */
        Grad(Tape<Scalar>& tape_, std::vector<Scalar> grads_) noexcept : tape(tape_), grads(grads_) {};  // Constructor
    };
}
