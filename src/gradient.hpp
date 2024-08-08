
#ifndef AUTOGRAD_GRADIENT_HPP
#define AUTOGRAD_GRADIENT_HPP


#include "utils.hpp"
#include "variable.hpp"

namespace AutoGrad {
  template<FloatingPoint Scalar>
  class Variable; // Forward declaration

  template<FloatingPoint Scalar>
  class Gradient {
    friend class Variable<Scalar>;

  public:
    Scalar withRespectTo(const Variable<Scalar> &variable) const {
      if (&tape != &variable.tape) {
        throw std::invalid_argument("`AutoGrad::Variable` not from the same `AutoGrad::Tape` as `AutoGrad::Gradient`");
      }
      return gradients[variable.index];
    }

  private:
    Tape<Scalar> &tape;
    std::vector<Scalar> gradients;

    Gradient(Tape<Scalar> &tape_, std::vector<Scalar> gradients_) : tape(tape_), gradients(gradients_) {}; // Constructor
  };
}


#endif // AUTOGRAD_GRADIENT_HPP
