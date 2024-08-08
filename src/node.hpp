
#ifndef AUTOGRAD_NODE_HPP
#define AUTOGRAD_NODE_HPP


#include "utils.hpp"

namespace AutoGrad {
  template<FloatingPoint Scalar>
  class Variable; // Forward declaration

  template<FloatingPoint Scalar>
  class Tape; // Forward declaration

  template<FloatingPoint Scalar>
  class Node {
    friend class Variable<Scalar>;
    friend class Tape<Scalar>;

  private:
    std::pair<Scalar, Scalar> weights;
    std::pair<size_t, size_t> dependencies;

    Node(std::pair<Scalar, Scalar> weights_, std::pair<size_t, size_t> dependencies_) : weights(weights_), dependencies(dependencies_) {}; // Constructor
  };
}


#endif // AUTOGRAD_NODE_HPP
