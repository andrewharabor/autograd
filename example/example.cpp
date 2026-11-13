
#include <iomanip>
#include <iostream>

#include "autograd.hpp"

using namespace AutoGrad;

int main() {
    Tape<double> tape;
    Var x = tape.var(0.5);
    Var y = tape.var(4.2);
    Var z = x * y + sin(x);
    Grad grad = z.grad();
    std::cout << std::setprecision(10);
    std::cout << "z = " << z.value() << std::endl;        // z = 2.579425539
    std::cout << "∂z/∂x = " << grad.wrt(x) << std::endl;  // ∂z/∂x = 5.077582562
    std::cout << "∂z/∂y = " << grad.wrt(y) << std::endl;  // ∂z/∂y = 0.5
}
