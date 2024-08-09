# AutoGrad

A C++ library for gradient computation via [reverse-mode automatic differentiation](https://en.wikipedia.org/wiki/Automatic_differentiation#Reverse_accumulation).

## Description

AutoGrad implements reverse-mode automatic differentiation (AD) using a tape-based representation. Specifically, the tape records mathematical operations (arithmetic and elementary functions) performed on variables bound to it and then accumulates the derivatives in reverse order to compute the gradient.

[Forward-mode AD](https://en.wikipedia.org/wiki/Automatic_differentiation#Forward_accumulation) differs in that the derivatives are accumulated directly alongside the operations performed on the variables. Reverse-mode AD is a generalization of [backpropagation](https://en.wikipedia.org/wiki/Backpropagation) and is preferred in the context of [gradient-based optimization problems](https://en.wikipedia.org/wiki/Gradient_descent) in machine learning (over forward-mode AD, [numerical differentiation](https://en.wikipedia.org/wiki/Numerical_differentiation), and [symbolic differentiation](https://en.wikipedia.org/wiki/Computer_algebra)) due to its efficiency, flexibility, and numerical stability.

Mathematically, given a function $`f : \mathbb{R}^{n} \rarr \mathbb{R}^{m}`$, reverse-mode AD computes the partial derivatives of a scalar output variable with respect to all input variables with a single pass. This means that it takes on the order of $`O(m)`$ time in order to compute the full [Jacobian](https://en.wikipedia.org/wiki/Jacobian_matrix_and_determinant). For optimizing neural networks, there are usually a large number of input parameters and a scalar output that denotes the loss ($`f : \mathbb{R}^{n} \rarr \mathbb{R}`$). Thus, reverse-mode AD can efficiently compute the entire gradient with a single backward pass.

## Usage

If you would like to use AutoGrad, follow these steps:

1. Clone this GitHub repository with one of the following commands:

``` bash
git clone https://github.com/andrewharabor/autograd.git
```

``` bash
git clone git@github.com:andrewharabor/autograd.git
```

2. Include the header file for AutoGrad in the C++ source file where you would like to use it:

``` cpp
#include <autograd.hpp>
```

3. Make sure to tell the compiler where to look for the header file. For example, with `g++`/`gcc`, pass the following flag:

``` bash
-I<PATH TO CLONED AUTOGRAD REPOSITORY>/autograd/src
```

Note that since the entirety of the AutoGrad library is templated, it is completely contained in `.hpp` files and so there is nothing to compile or link with. See [Limitations](#limitations) for more details.

## Example

The file [example.cpp](/example/example.cpp) (copied below for convenience) shows a simple use case of the AutoGrad library.

``` cpp
#include <iomanip>
#include <iostream>

#include "autograd.hpp"

int main() {
  AutoGrad::Tape<double> tape;
  AutoGrad::Variable<double> x = tape.variable(0.5);
  AutoGrad::Variable<double> y = tape.variable(4.2);
  AutoGrad::Variable<double> z = x * y + AutoGrad::sin(x);
  AutoGrad::Gradient<double> grad = z.gradient();
  std::cout << std::setprecision(10);
  std::cout << "z = " << z.value() << std::endl; // z = 2.579425539
  std::cout << "∂z/∂x = " << grad.withRespectTo(x) << std::endl; // ∂z/∂x = 5.077582562
  std::cout << "∂z/∂y = " << grad.withRespectTo(y) << std::endl; // ∂z/∂y = 0.5
}
```

Here, a `Tape` object is initialized and `Variable`s $`x = 0.5`$ and $`y = 4.2`$ are bound to it. The expression $`z = xy + sin(x)`$ and the partial derivatives $`\frac{\partial z}{\partial x}`$ and $`\frac{\partial z}{\partial y}`$ are computed. Notice how the gradient is computed once and stored in a `Gradient` object. This allows the partial derivative of the output variable with respect to any input variable to be retrieved in constant time.

To run the example yourself, clone the repository as described in [Usage](#usage) and `cd` into the `autograd` directory. Then run the following commands:

``` bash
make
./build/main
```

To clean up the output directory `build`, run:

``` bash
make clean
```

## Limitations

While AutoGrad is a complete library, there are some areas in which it could use some improvements:

- **There is only support for reverse-mode AD and first-order derivatives.**
- **No direct support for linear algebra operations or Jacobians.** This means that the user would have to create their own `Matrix`/`Tensor` class that correctly interfaces with the AutoGrad library and that implements a way to directly compute Jacobians.
- **None of the mathematical functions implemented by AutoGrad do any domain checking.** This leads to cases where evaluating a function is undefined but the derivative seems reasonable even though it should be invalid. For example, computing $`log(-2)`$ results in `-nan` but AutoGrad reports the gradient as $`-0.5`$ (since the derivative of $`log(x)`$ is $`\frac{1}{x}`$) when really it should also be undefined. It is deemed the responsibility of the user to ensure this doesn't happen and handle it accordingly.
- **The entirety of AutoGrad is contained solely in `.hpp` header files.** Because the C++ compiler needs access to an entire template definition in order to instantiate it at compile-time, templates cannot be declared and defined separately (see [this](https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file)). Of course, there are workarounds (see [this](https://stackoverflow.com/questions/44774036/why-use-a-tpp-file-when-implementing-templated-functions-and-classes-defined-i)) but since AutoGrad significantly relies on `friend` classes and functions, it would lead to even more boilerplate code and bloat than already exists. Furthermore, this means that there is some compile-time overhead from including entire class definitions and that users implicitly gain access to headers like `<cmath>` that AutoGrad includes for internal use. On the upside, we don't have to go through the trouble of dealing with the C/C++ linker!

## References

- [Reverse-mode automatic differentiation: a tutorial](https://rufflewind.com/2016-12-30/reverse-mode-automatic-differentiation) (article) and [revad](https://github.com/Rufflewind/revad) (GitHub repository)

- [What's Automatic Differentiation?](https://huggingface.co/blog/andmholm/what-is-automatic-differentiation) (article)

- [What is Automatic Differentiation?](https://www.youtube.com/watch?v=wG_nF1awSSY) (YouTube video)

- [Automatic Differentiation: Differentiate (almost) any function](https://www.youtube.com/watch?v=4wgXBr7fnQg) (YouTube video)

- [Automatic Differentiation Explained with Example](https://www.youtube.com/watch?v=jS-0aAamC64) (YouTube video)

- [simple-autodiff](https://github.com/gtoubassi/simple-autodiff) (GitHub repository)

- [Automatic Differentiation](https://en.wikipedia.org/wiki/Automatic_differentiation) (Wikipedia article)
