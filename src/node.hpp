#pragma once

#include "utils.hpp"

namespace AutoGrad {
    template<FloatingPoint Scalar>
    class Var;  // Forward declaration

    template<FloatingPoint Scalar>
    class Tape;  // Forward declaration

    /* Represents an intermediate variable in the compuational graph used for reverse-mode automatic differentiation.
    Note that this class is only for internal use and has no public members or functions. */
    template<FloatingPoint Scalar>
    class Node {
        friend class Var<Scalar>;
        friend class Tape<Scalar>;

    private:
        std::pair<Scalar, Scalar> weights;  // Derivative of the node's output with respect to the node's input.
        std::pair<size_t, size_t> deps;     // Indices to parent nodes in the computational graph.

        /* Construct a node object from a set of weights and dependencies. */
        Node(std::pair<Scalar, Scalar> weights_, std::pair<size_t, size_t> deps_) noexcept :
            weights(weights_), deps(deps_) {};  // Constructor
    };
}
