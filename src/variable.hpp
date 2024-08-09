
#ifndef AUTOGRAD_VARIABLE_HPP
#define AUTOGRAD_VARIABLE_HPP


#include "gradient.hpp"
#include "node.hpp"
#include "tape.hpp"
#include "utils.hpp"

namespace AutoGrad {
  template<FloatingPoint Scalar>
  class Tape; // Forward declaration

  template<FloatingPoint Scalar>
  class Gradient; // Forward declaration

  /* A floating-point variable type that uses information about operations performed on it in order to offer gradient
  computation. */
  template<FloatingPoint Scalar>
  class Variable {
    friend class Tape<Scalar>;
    friend class Gradient<Scalar>;

    // A bunch of arithmetic operations and elementary mathematical functions that have to be declared as friends so
    // that they can access private members and methods.
    // I know it's ugly but I don't think there is another option aside from making class internals public.

    template<FloatingPoint S>
    friend Variable<S> operator+(const Variable<S> &variable1, const Variable<S> &variable2);

    template<FloatingPoint S>
    friend Variable<S> operator+(const Variable<S> &variable, S scalar);

    template<FloatingPoint S>
    friend Variable<S> operator+(S scalar, const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> operator+(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable1, const Variable<S> &variable2);

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable, S scalar);

    template<FloatingPoint S>
    friend Variable<S> operator-(S scalar, const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> operator*(const Variable<S> &variable1, const Variable<S> &variable2);

    template<FloatingPoint S>
    friend Variable<S> operator*(const Variable<S> &variable, S scalar);

    template<FloatingPoint S>
    friend Variable<S> operator*(S scalar, const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> operator/(const Variable<S> &variable1, const Variable<S> &variable2);

    template<FloatingPoint S>
    friend Variable<S> operator/(const Variable<S> &variable, S scalar);

    template<FloatingPoint S>
    friend Variable<S> operator/(S scalar, const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> pow(const Variable<S> &variable1, const Variable<S> &variable2);

    template<FloatingPoint S>
    friend Variable<S> pow(const Variable<S> &variable, S scalar);

    template<FloatingPoint S>
    friend Variable<S> pow(S scalar, const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> sqrt(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> cbrt(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> exp(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> exp2(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> log(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> log(const Variable<S> &variable, const Variable<S> &base);

    template<FloatingPoint S>
    friend Variable<S> log(const Variable<S> &variable, S base);

    template<FloatingPoint S>
    friend Variable<S> log(S scalar, const Variable<S> &base);

    template<FloatingPoint S>
    friend Variable<S> ln(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> log2(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> log10(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> sin(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> cos(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> tan(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> sec(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> csc(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> cot(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arcsin(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arccos(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arctan(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arcsec(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arccsc(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arccot(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> sinh(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> cosh(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> tanh(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> sech(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> csch(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> coth(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arsinh(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arcosh(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> artanh(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arsech(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arcsch(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> arcoth(const Variable<S> &variable);

    template<FloatingPoint S>
    friend Variable<S> abs(const Variable<S> &variable);

  public:

    /* Construct a new variable object by copying the value of the given one. */
    Variable(const Variable<Scalar> &variable) : tape(variable.tape), val{variable.val} {  // Copy constructor
      index = tape.push_back(1.0, variable.index);
    }

    /* Construct a new variable object by moving the given one. */
    Variable(Variable<Scalar> &&variable) = default; // Move constructor

    // Disallow reassignment operations
    Variable<Scalar> &operator=(const Variable<Scalar> &variable) = delete; // Copy assignment operator
    Variable<Scalar> &operator=(Variable<Scalar> &&variable) = delete; // Move assignment operator

    /* Retrive the actual numerical value. */
    Scalar value() const {
      return val;
    }

    /* Compute the gradient: the partial derivatives with respect to all input variables. */
    Gradient<Scalar> gradient() const {
      size_t size = tape.nodes.size();
      std::vector<Scalar> gradients(size, 0.0);
      gradients[index] = 1.0;
      for (size_t i = size; i-- > 0;) {
        Node<Scalar> &node = tape.nodes[i];
        gradients[node.dependencies.first] += node.weights.first * gradients[i];
        gradients[node.dependencies.second] += node.weights.second * gradients[i];
      }
      return Gradient<Scalar>(tape, gradients);
    }

  private:
    Tape<Scalar> &tape; // Tape that the variable was created on.
    Scalar val; //  Actual numerical value.
    size_t index; // Index in the computational graph held by the tape.

    /* Construct a variable object for a particular tape given a value and an index. */
    Variable(Tape<Scalar> &tape_, Scalar value_, size_t index_) : tape(tape_), val{value_}, index{index_} {} // Constructor
  };
}


#endif // AUTOGRAD_VARIABLE_HPP
