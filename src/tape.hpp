
#ifndef AUTOGRAD_TAPE_HPP
#define AUTOGRAD_TAPE_HPP


#include "node.hpp"
#include "utils.hpp"
#include "variable.hpp"

namespace AutoGrad {
  template<FloatingPoint Scalar>
  class Variable; // Forward declaration

  template<FloatingPoint Scalar>
  class Gradient; // Forward declaration

  /* A gradient tape that stores a computational graph recording mathematical operations perfomed on variables in order
  to compute derivatives. */
  template<FloatingPoint Scalar>
  class Tape {
    friend class Variable<Scalar>;
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
    friend Variable<S> operator-(const Variable<S> &variable1, const Variable<S> &variable2);

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable, S scalar);

    template<FloatingPoint S>
    friend Variable<S> operator-(S scalar, const Variable<S> &variable);

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
    /* Construct a new tape object. */
    Tape() noexcept = default; // Default constructor

    // Disallow copy semantics
    Tape(const Tape<Scalar> &tape) noexcept = delete; // Copy constructor
    Tape<Scalar> &operator=(const Tape<Scalar> &tape) noexcept = delete; // Copy assignment operator

    // But allow move semantics

    /* Construct a new tape object by moving the given one. */
    Tape(Tape<Scalar> &&tape) noexcept = default; // Move constructor

    /* Assign a new tape by moving the given one. */
    Tape<Scalar> &operator=(Tape<Scalar> &&tape) noexcept = default; // Move assignment operator

    /* Instantiate a new variable object (that is permanently bound to the tape) as part of the computational graph. */
    Variable<Scalar> variable(Scalar value) {
      return Variable<Scalar>(*this, value, push_back());
    }

  private:
    std::vector<Node<Scalar>> nodes; // Internal representation of the computational graph.

    /* Add an empty node to the computational graph that represents a new variable. */
    size_t push_back() {
      size_t size = nodes.size();
      nodes.push_back(Node<Scalar>(std::make_pair(0.0, 0.0), std::make_pair(size, size)));
      return size;
    }

    /* Add a node to the computational graph that stores the result of a unary operation. */
    size_t push_back(Scalar weight, size_t dependency) {
      size_t size = nodes.size();
      nodes.push_back(Node<Scalar>(std::make_pair(weight, 0.0), std::make_pair(dependency, size)));
      return size;
    }

    /* Add a node to the computational graph that stores the result of a binary operation. */
    size_t push_back(Scalar weight1, size_t dependency1, Scalar weight2, size_t dependency2) {
      size_t size = nodes.size();
      nodes.push_back(Node<Scalar>(std::make_pair(weight1, weight2), std::make_pair(dependency1, dependency2)));
      return size;
    }
  };
}


#endif // AUTOGRAD_TAPE_HPP
