
#ifndef AUTOGRAD_NODE_HPP
#define AUTOGRAD_NODE_HPP


#include "utils.hpp"

namespace AutoGrad {
  template<FloatingPoint Scalar>
  class Variable; // Forward declaration

  template<FloatingPoint Scalar>
  class Tape; // Forward declaration

  /* Represents an intermediate variable in the compuational graph used for reverse-mode automatic differentiation.
  Note that this class is only for internal use and has no public members or functions. */
  template<FloatingPoint Scalar>
  class Node {
    friend class Variable<Scalar>;
    friend class Tape<Scalar>;

  private:
    std::pair<Scalar, Scalar> weights; // Derivative of the node's output with respect to the node's input.
    std::pair<size_t, size_t> dependencies; // Indices to parent nodes in the computational graph.

    /* Construct a node object from a set of weights and dependencies. */
    Node(std::pair<Scalar, Scalar> weights_, std::pair<size_t, size_t> dependencies_) : weights(weights_), dependencies(dependencies_) {}; // Constructor
  };
}


#endif // AUTOGRAD_NODE_HPP
