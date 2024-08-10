
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

    // Comparison operators

    // /* Spaceship operator (implements all relational operators). */
    // template<FloatingPoint S>
    // friend constexpr auto operator<=>(const Variable<S> &variable1, const Variable<S> &variable2) noexcept {
    //   return variable1.val <=> variable2.val;
    // }

    /* Equality.
    NOTE: this directly compares two floating-point values using `==` and is therefore unsafe. */
    template<FloatingPoint S>
    friend bool operator==(const Variable<S> &variable1, const Variable<S> &variable2) {
      return variable1.val == variable2.val;
    }

    /* Inequality.
    NOTE: this directly compares two floating-point values using `!=` and is therefore unsafe. */
    template<FloatingPoint S>
    friend bool operator!=(const Variable<S> &variable1, const Variable<S> &variable2) {
      return variable1.val != variable2.val;
    }

    /* Greater than. */
    template<FloatingPoint S>
    friend bool operator>(const Variable<S> &variable1, const Variable<S> &variable2) {
      return variable1.val > variable2.val;
    }

    /* Less than. */
    template<FloatingPoint S>
    friend bool operator<(const Variable<S> &variable1, const Variable<S> &variable2) {
      return variable1.val < variable2.val;
    }

    /* Greater than or equal to. */
    template<FloatingPoint S>
    friend bool operator>=(const Variable<S> &variable1, const Variable<S> &variable2) {
      return variable1.val >= variable2.val;
    }

    /* Less than or equal to. */
    template<FloatingPoint S>
    friend bool operator<=(const Variable<S> &variable1, const Variable<S> &variable2) {
      return variable1.val <= variable2.val;
    }

    // A bunch of arithmetic operations and elementary mathematical functions that have to be declared as friends so
    // that they can access private members and methods.
    // I know it's ugly but I don't think there is another option aside from making class internals public.

    // Arithmetic operations

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

    // Exponential and logarithmic functions

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

    // Trigonometric functions

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

    // Hyperbolic trigonometric functions

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
    Variable(const Variable<Scalar> &variable) noexcept : tape(variable.tape), val{variable.val} {  // Copy constructor
      index = tape.push_back(1.0, variable.index);
    }

    /* Construct a new variable object by moving the given one. */
    Variable(Variable<Scalar> &&variable) noexcept = default; // Move constructor

    // Assignment operators

    /* Reassign a variable object by copying the value of the given one. */
    Variable<Scalar> &operator=(const Variable<Scalar> &variable) {
      if (this != &variable) {
        if (&tape != &variable.tape) {
          throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
        }
        val = variable.val;
        index = tape.push_back(1.0, variable.index);
      }
      return *this;
    }

    /* Reassign a variable object by moving the given one. */
    Variable<Scalar> &operator=(Variable<Scalar> &&variable) {
      if (&tape != &variable.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      val = variable.val;
      index = variable.index;
      return *this;
    }

    /* Reassign a variable object using a scalar. */
    Variable<Scalar> &operator=(Scalar scalar) {
      val = scalar;
      index = tape.push_back();
      return *this;
    }

    /* Addition assignment. */
    Variable<Scalar> &operator+=(const Variable<Scalar> &variable) {
      *this = *this + variable;
      return *this;
    }

    /* Addition assignment. */
    Variable<Scalar> &operator+=(Scalar scalar) {
      *this = *this + scalar;
      return *this;
    }

    /* Subtraction assignment. */
    Variable<Scalar> &operator-=(const Variable<Scalar> &variable) {
      *this = *this - variable;
      return *this;
    }

    /* Subtraction assignment. */
    Variable<Scalar> &operator-=(Scalar scalar) {
      *this = *this - scalar;
      return *this;
    }

    /* Multiplication assignment. */
    Variable<Scalar> &operator*=(const Variable<Scalar> &variable) {
      *this = *this * variable;
      return *this;
    }

    /* Multiplication assignment. */
    Variable<Scalar> &operator*=(Scalar scalar) {
      *this = *this * scalar;
      return *this;
    }

    /* Division assignment. */
    Variable<Scalar> &operator/=(const Variable<Scalar> &variable) {
      *this = *this / variable;
      return *this;
    }

    /* Division assignment. */
    Variable<Scalar> &operator/=(Scalar scalar) {
      *this = *this / scalar;
      return *this;
    }

    /* Identity. */
    Variable<Scalar> operator+() const {
      return Variable<Scalar>(tape, val, tape.push_back(1.0, index));
    }

    /* Negation. */
    Variable<Scalar> operator-() const {
      return Variable<Scalar>(tape, -val, tape.push_back(-1.0, index));
    }

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
    Variable(Tape<Scalar> &tape_, Scalar value_, size_t index_) noexcept : tape(tape_), val{value_}, index{index_} {} // Constructor
  };
}


#endif // AUTOGRAD_VARIABLE_HPP
