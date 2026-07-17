#include "linalg/matrix.h"

#include <array>
#include <print>

void run_linalg_demo() {
    std::println("=== Linear Algebra Demo ===\n");

    // 3x3 matrix from array
    std::array<float, 9> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<float, 3, 3> A(data);
    std::println("Matrix A:");
    A.print();

    // Identity
    auto I = Matrix<float, 3, 3>::identity();
    std::println("\nIdentity:");
    I.print();

    // Addition
    auto C = A + A;
    std::println("\nA + A:");
    C.print();

    // Matrix multiply
    auto P = A * A;
    std::println("\nA * A:");
    P.print();

    // Matrix-vector multiply
    std::array<float, 3> vec = {1, 2, 3};
    auto v = A * vec;
    std::println("\nA * [1,2,3] = [{}, {}, {}]", v[0], v[1], v[2]);

    // Compile-time matrix (constexpr)
    constexpr std::array<double, 4> d = {1, 2, 3, 4};
    constexpr Matrix<double, 2, 2> M(d);
    constexpr auto M2 = M * M;
    std::println("\nconstexpr M*M: [{}, {}; {}, {}]",
                 M2(0, 0), M2(0, 1), M2(1, 0), M2(1, 1));
}
