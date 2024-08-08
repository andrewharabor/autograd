
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

  template<FloatingPoint Scalar>
  class Variable {
    friend class Tape<Scalar>;
    friend class Gradient<Scalar>;

    template<FloatingPoint S>
    friend Variable<S> operator+(const Variable<S> &variable1, const Variable<S> &variable2) {
      if (&variable1.tape != &variable2.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      return Variable<S>(variable1.tape, variable1.val + variable2.val, variable1.tape.push_back(1.0, variable1.index, 1.0, variable2.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator+(const Variable<S> &variable, S scalar) {
      return Variable<S>(variable.tape, variable.val + scalar, variable.tape.push_back(1.0, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator+(S scalar, const Variable<S> &variable) {
      return variable + scalar;
    }

    template<FloatingPoint S>
    friend Variable<S> operator+(const Variable<S> &variable) {
      return Variable<S>(variable.tape, variable.val, variable.tape.push_back(1.0, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable1, const Variable<S> &variable2) {
      if (&variable1.tape != &variable2.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      return Variable<S>(variable1.tape, variable1.val - variable2.val, variable1.tape.push_back(1.0, variable1.index, -1.0, variable2.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable, S scalar) {
      return Variable<S>(variable.tape, variable.val - scalar, variable.tape.push_back(1.0, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator-(S scalar, const Variable<S> &variable) {
      return Variable<S>(variable.tape, scalar - variable.val, variable.tape.push_back(-1.0, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator-(const Variable<S> &variable) {
      return Variable<S>(variable.tape, -variable.val, variable.tape.push_back(-1.0, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator*(const Variable<S> &variable1, const Variable<S> &variable2) {
      if (&variable1.tape != &variable2.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      return Variable<S>(variable1.tape, variable1.val * variable2.val, variable1.tape.push_back(variable2.val, variable1.index, variable1.val, variable2.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator*(const Variable<S> &variable, S scalar) {
      return Variable<S>(variable.tape, variable.val * scalar, variable.tape.push_back(scalar, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator*(S scalar, const Variable<S> &variable) {
      return variable * scalar;
    }

    template<FloatingPoint S>
    friend Variable<S> operator/(const Variable<S> &variable1, const Variable<S> &variable2) {
      if (&variable1.tape != &variable2.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      return Variable<S>(variable1.tape, variable1.val / variable2.val, variable1.tape.push_back(1.0 / variable2.val, variable1.index, -variable1.val / (variable2.val * variable2.val), variable2.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator/(const Variable<S> &variable, S scalar) {
      return Variable<S>(variable.tape, variable.val / scalar, variable.tape.push_back(1.0 / scalar, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> operator/(S scalar, const Variable<S> &variable) {
      return Variable<S>(variable.tape, scalar / variable.val, variable.tape.push_back(-scalar / (variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> pow(const Variable<S> &variable1, const Variable<S> &variable2) {
      if (&variable1.tape != &variable2.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      return Variable<S>(variable1.tape, std::pow(variable1.val, variable2.val), variable1.tape.push_back(variable2.val * std::pow(variable1.val, variable2.val - 1), variable1.index, std::log(variable1.val) * std::pow(variable1.val, variable2.val), variable2.index));
    }

    template<FloatingPoint S>
    friend Variable<S> pow(const Variable<S> &variable, S scalar) {
      return Variable<S>(variable.tape, std::pow(variable.val, scalar), variable.tape.push_back(scalar * std::pow(variable.val, scalar - 1), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> pow(S scalar, const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::pow(scalar, variable.val), variable.tape.push_back(std::log(scalar) * std::pow(scalar, variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> sqrt(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::sqrt(variable.val), variable.tape.push_back(0.5 / std::sqrt(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> cbrt(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::cbrt(variable.val), variable.tape.push_back(1.0 / (3.0 * std::cbrt(variable.val) * std::cbrt(variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> exp(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::exp(variable.val), variable.tape.push_back(std::exp(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> exp2(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::exp2(variable.val), variable.tape.push_back(std::exp2(variable.val) * std::log(2), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> log(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::log(variable.val), variable.tape.push_back(1.0 / variable.val, variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> log(const Variable<S> &variable, const Variable<S> &base) {
      if (&variable.tape != &base.tape) {
        throw std::invalid_argument("`AutoGrad::Variable`s not from the same `AutoGrad::Tape`");
      }
      return Variable<S>(variable.tape, std::log(variable.val) / std::log(base.val), variable.tape.push_back(1.0 / (variable.val * std::log(base.val)), variable.index, -std::log(variable.val) / (base.val * std::log(base.val) * std::log(base.val)), base.index));
    }

    template<FloatingPoint S>
    friend Variable<S> log(const Variable<S> &variable, S base) {
      return Variable<S>(variable.tape, std::log(variable.val) / std::log(base), variable.tape.push_back(1.0 / (variable.val * std::log(base)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> log(S scalar, const Variable<S> &base) {
      return Variable<S>(base.tape, std::log(scalar) / std::log(base.val), base.tape.push_back(-std::log(scalar) / (base.val * std::log(base.val) * std::log(base.val)), base.index));
    }

    template<FloatingPoint S>
    friend Variable<S> ln(const Variable<S> &variable) {
      return log(variable);
    }

    template<FloatingPoint S>
    friend Variable<S> log2(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::log2(variable.val), variable.tape.push_back(1.0 / (variable.val * std::log(2)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> log10(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::log10(variable.val), variable.tape.push_back(1.0 / (variable.val * std::log(10)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> sin(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::sin(variable.val), variable.tape.push_back(std::cos(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> cos(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::cos(variable.val), variable.tape.push_back(-std::sin(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> tan(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::tan(variable.val), variable.tape.push_back(1.0 / (std::cos(variable.val) * std::cos(variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> sec(const Variable<S> &variable) {
      return Variable<S>(variable.tape, 1.0 / std::cos(variable.val), variable.tape.push_back(std::tan(variable.val) / std::cos(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> csc(const Variable<S> &variable) {
      return Variable<S>(variable.tape, 1.0 / std::sin(variable.val), variable.tape.push_back(-std::cos(variable.val) / (std::sin(variable.val) * std::sin(variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> cot(const Variable<S> &variable) {
      return Variable<S>(variable.tape, 1.0 / std::tan(variable.val), variable.tape.push_back(-1.0 / (std::sin(variable.val) * std::sin(variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arcsin(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::asin(variable.val), variable.tape.push_back(1.0 / std::sqrt(1.0 - variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arccos(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::acos(variable.val), variable.tape.push_back(-1.0 / std::sqrt(1.0 - variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arctan(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::atan(variable.val), variable.tape.push_back(1.0 / (1.0 + variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arcsec(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::acos(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(variable.val * variable.val - 1.0)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arccsc(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::asin(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(variable.val * variable.val - 1.0)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arccot(const Variable<S> &variable) {
      return Variable<S>(variable.tape, (variable.val >= 0) ? (std::atan(1.0 / variable.val)) : (std::atan(1.0 / variable.val) + std::numbers::pi_v<S>), variable.tape.push_back(-1.0 / (1.0 + variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> sinh(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::sinh(variable.val), variable.tape.push_back(std::cosh(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> cosh(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::cosh(variable.val), variable.tape.push_back(std::sinh(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> tanh(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::tanh(variable.val), variable.tape.push_back(1.0 - std::tanh(variable.val) * std::tanh(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> sech(const Variable<S> &variable) {
      return Variable<S>(variable.tape, 1.0 / std::cosh(variable.val), variable.tape.push_back(-std::tanh(variable.val) / std::cosh(variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> csch(const Variable<S> &variable) {
      return Variable<S>(variable.tape, 1.0 / std::sinh(variable.val), variable.tape.push_back(-std::cosh(variable.val) / (std::sinh(variable.val) * std::sinh(variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> coth(const Variable<S> &variable) {
      return Variable<S>(variable.tape, 1.0 / std::tanh(variable.val), variable.tape.push_back(-1.0 / (std::sinh(variable.val) * std::sinh(variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arsinh(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::asinh(variable.val), variable.tape.push_back(1.0 / std::sqrt(variable.val * variable.val + 1.0), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arcosh(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::acosh(variable.val), variable.tape.push_back(1.0 / std::sqrt(variable.val * variable.val - 1.0), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> artanh(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::atanh(variable.val), variable.tape.push_back(1.0 / (1.0 - variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arsech(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::acosh(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(1.0 - variable.val * variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arcsch(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::asinh(1.0 / variable.val), variable.tape.push_back(-1.0 / (std::abs(variable.val) * std::sqrt(1.0 + variable.val * variable.val)), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> arcoth(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::atanh(1.0 / variable.val), variable.tape.push_back(1.0 / (1.0 - variable.val * variable.val), variable.index));
    }

    template<FloatingPoint S>
    friend Variable<S> abs(const Variable<S> &variable) {
      return Variable<S>(variable.tape, std::abs(variable.val), variable.tape.push_back(std::abs(variable.val) / variable.val, variable.index));
    }

  public:
    Variable(const Variable<Scalar> &variable) : tape(variable.tape), val{variable.val} {  // Copy constructor
      index = tape.push_back(1.0, variable.index);
    }

    Variable(Variable<Scalar> &&variable) = default; // Move constructor

    // Disallow reassignment operations
    Variable<Scalar> &operator=(const Variable<Scalar> &variable) = delete; // Copy assignment operator
    Variable<Scalar> &operator=(Variable<Scalar> &&variable) = delete; // Move assignment operator

    Scalar value() const {
      return val;
    }

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
    Tape<Scalar> &tape;
    Scalar val;
    size_t index;

    Variable(Tape<Scalar> &tape_, Scalar value_, size_t index_) : tape(tape_), val{value_}, index{index_} {} // Constructor
  };
}


#endif // AUTOGRAD_VARIABLE_HPP
