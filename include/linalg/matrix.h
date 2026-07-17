#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <print>
#include <span>

template <std::floating_point T, std::size_t Rows, std::size_t Cols>
class Matrix {
public:
    constexpr Matrix() = default;

    constexpr explicit Matrix(std::span<const T, Rows * Cols> data) {
        std::copy(data.begin(), data.end(), data_.begin());
    }

    constexpr T& operator()(std::size_t r, std::size_t c) { return data_[r * Cols + c]; }
    constexpr const T& operator()(std::size_t r, std::size_t c) const { return data_[r * Cols + c]; }

    constexpr static Matrix identity() requires (Rows == Cols) {
        Matrix m{};
        for (std::size_t i = 0; i < Rows; ++i)
            m(i, i) = T{1};
        return m;
    }

    constexpr Matrix operator+(const Matrix& rhs) const {
        Matrix result{};
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            result.data_[i] = data_[i] + rhs.data_[i];
        return result;
    }

    constexpr Matrix operator*(const Matrix& rhs) const requires (Cols == Rows) {
        Matrix result{};
        for (std::size_t r = 0; r < Rows; ++r)
            for (std::size_t c = 0; c < Cols; ++c)
                for (std::size_t k = 0; k < Cols; ++k)
                    result(r, c) += (*this)(r, k) * rhs(k, c);
        return result;
    }

    constexpr std::array<T, Rows> operator*(const std::array<T, Cols>& vec) const {
        std::array<T, Rows> result{};
        for (std::size_t r = 0; r < Rows; ++r)
            for (std::size_t c = 0; c < Cols; ++c)
                result[r] += (*this)(r, c) * vec[c];
        return result;
    }

    void print() const {
        for (std::size_t r = 0; r < Rows; ++r) {
            std::print("  [");
            for (std::size_t c = 0; c < Cols; ++c)
                std::print("{:8.3f}{}", (*this)(r, c), c + 1 < Cols ? ", " : "");
            std::println("]");
        }
    }

    static constexpr std::size_t rows() { return Rows; }
    static constexpr std::size_t cols() { return Cols; }

private:
    std::array<T, Rows * Cols> data_{};
};

void run_linalg_demo();
