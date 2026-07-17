#include "simd/ops.h"

#include <chrono>
#include <print>
#include <vector>

namespace {

void add_scalar(const float* a, const float* b, float* out, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i)
        out[i] = a[i] + b[i];
}

void add_simd(const float* a, const float* b, float* out, std::size_t n) {
    constexpr std::size_t W = stdx::native_simd<float>::size();
    std::size_t i = 0;
    for (; i + W <= n; i += W) {
        stdx::native_simd<float> va, vb;
        va.copy_from(&a[i], stdx::element_aligned);
        vb.copy_from(&b[i], stdx::element_aligned);
        auto vc = va + vb;
        vc.copy_to(&out[i], stdx::element_aligned);
    }
    for (; i < n; ++i)
        out[i] = a[i] + b[i];
}

}  // namespace

void run_simd_demo() {
    std::println("=== SIMD Demo ===\n");

    constexpr std::size_t N = 1024;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), c(N);

    std::println("SIMD width: {} floats", stdx::native_simd<float>::size());

    // scalar
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < 10000; ++iter)
        add_scalar(a.data(), b.data(), c.data(), N);
    auto t1 = std::chrono::high_resolution_clock::now();

    // simd
    auto t2 = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < 10000; ++iter)
        add_simd(a.data(), b.data(), c.data(), N);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto scalar_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    auto simd_us = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

    std::println("Scalar: {} us (sum={})", scalar_us, c[0]);
    std::println("SIMD:   {} us (sum={})", simd_us, c[0]);
    std::println("Speedup: {:.2f}x", static_cast<double>(scalar_us) / simd_us);
}
