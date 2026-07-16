#pragma once

#include <concepts>
#include <expected>
#include <string>
#include <string_view>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

enum class Op { Add, Sub, Mul, Div };

struct Command {
    Op op;
    double lhs;
    double rhs;
};

using CalcResult = std::expected<double, std::string>;
