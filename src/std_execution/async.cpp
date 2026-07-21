#include "std_execution/async.h"

#include <algorithm>
#include <numeric>
#include <print>
#include <random>

void run_execution_demo() {
    std::println("=== std::execution Demo ===\n");

    // Generate sample trades
    std::vector<Trade> trades;
    // Obtain a random seed from the hardware
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> price_dist(100.0, 500.0);
    std::uniform_int_distribution<> qty_dist(1, 1000);

    const char* symbols[] = {"AAPL", "MSFT", "GOOG", "AMZN", "NVDA"};
    for (int i = 0; i < 20000; ++i) {
        trades.push_back({
            .id = i + 1,
            .symbol = symbols[i % 5],
            .price = price_dist(gen),
            .quantity = qty_dist(gen),
        });
    }

    // Parallel sort using execution policy
    std::sort(std::execution::par, trades.begin(), trades.end(),
              [](const Trade& a, const Trade& b) { return a.price > b.price; });

    std::println("Top 5 trades by price (parallel sorted):");
    for (int i = 0; i < 5 && i < static_cast<int>(trades.size()); ++i) {
        std::println("  {} {:>5} @ ${:.2f} x {}",
                     trades[i].id, trades[i].symbol, trades[i].price, trades[i].quantity);
    }

    // Parallel transform: compute notional value
    std::vector<double> notionals(trades.size());
    std::transform(std::execution::par, trades.begin(), trades.end(), notionals.begin(),
                   [](const Trade& t) { return t.price * t.quantity; });

    // Parallel reduce: total notional
    double total = std::reduce(std::execution::par, notionals.begin(), notionals.end(), 0.0);

    std::println("\nTotal notional: ${:.2f}", total);
}
