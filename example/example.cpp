
// #include <iomanip>
// #include <iostream>

// #include "autograd.hpp"

// int main() {
//   AutoGrad::Tape<double> tape;
//   AutoGrad::Variable<double> x = tape.variable(0.5);
//   AutoGrad::Variable<double> y = tape.variable(4.2);
//   AutoGrad::Variable<double> z = x * y + AutoGrad::sin(x);
//   AutoGrad::Gradient<double> grad = z.gradient();
//   std::cout << std::setprecision(10);
//   std::cout << "z = " << z.value() << std::endl; // z = 2.579425539
//   std::cout << "∂z/∂x = " << grad.withRespectTo(x) << std::endl; // ∂z/∂x = 5.077582562
//   std::cout << "∂z/∂y = " << grad.withRespectTo(y) << std::endl; // ∂z/∂y = 0.5
// }


#include <iomanip>
#include <iostream>

#include "autograd.hpp"

int main() {
  AutoGrad::Tape<double> tape;
  AutoGrad::Variable<double> x = tape.variable(3.3);
  AutoGrad::Variable<double> y = x * x;
  y *= x;
  AutoGrad::Gradient<double> grad = y.gradient();
  std::cout << std::setprecision(10) << grad.withRespectTo(x) << std::endl;
}
