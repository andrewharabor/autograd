
#ifndef AUTOGRAD_GRADIENT_HPP
#define AUTOGRAD_GRADIENT_HPP


#include "utils.hpp"
#include "variable.hpp"

namespace AutoGrad {
  template<FloatingPoint Scalar>
  class Variable; // Forward declaration

  /* Contains information about the gradient of a particular tape: the partial derivatives of a single output variable
  with respect to all input variables. */
  template<FloatingPoint Scalar>
  class Gradient {
    friend class Variable<Scalar>;

  public:

    /* Retrieve the partial derivative with respect to the given variable. */
    Scalar withRespectTo(const Variable<Scalar> &variable) const {
      if (&tape != &variable.tape) {
        throw std::invalid_argument("`AutoGrad::Variable` not from the same `AutoGrad::Tape` as `AutoGrad::Gradient`");
      }
      return gradients[variable.index];
    }

  private:
    Tape<Scalar> &tape; // Tape that the gradient was computed on.
    std::vector<Scalar> gradients; // Partial derivatives w.r.t each input variable.

    /* Construct a gradient object for a particular tape given the gradients. */
    Gradient(Tape<Scalar> &tape_, std::vector<Scalar> gradients_) noexcept : tape(tape_), gradients(gradients_) {}; // Constructor
  };
}


#endif // AUTOGRAD_GRADIENT_HPP
