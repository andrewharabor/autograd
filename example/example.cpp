
#include <iomanip>
#include <iostream>

#include "autograd.hpp"

int main() {
  AutoGrad::Tape<double> tape;
  AutoGrad::Variable<double> x = tape.variable(0.5);
  AutoGrad::Variable<double> y = tape.variable(4.2);
  AutoGrad::Variable<double> z = x * y + sin(x);
  AutoGrad::Gradient<double> grad = z.gradient();
  std::cout << std::setprecision(25);
  std::cout << "z = " << z.value() << std::endl; // z = 2.5794255386042030941951
  std::cout << "∂z/∂x = " << grad.withRespectTo(x) << std::endl; // ∂z/∂x = 5.077582561890372936375115
  std::cout << "∂z/∂y = " << grad.withRespectTo(y) << std::endl; // ∂z/∂y = 0.5
}
