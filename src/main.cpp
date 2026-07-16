#include "calculator.h"
#include "logger.h"
#include "pgsql/db_pgsql.h"
#include "pgsql/repos/stock_ticker_repo.h"

#include <unistd.h>
#include <print>

int main() {
    std::println("=== C++26 Hands-On ===\n");

    run_calculator_demo();
    log_stacktrace("main");

    std::println("\n=== PostgreSQL CRUD ===\n");

    try {
        DbPgsql db;
        StockTickerRepo repo(db);

        // find all
        auto all = repo.find_all();
        if (all) {
            std::println("All tickers ({}):", all->size());
            for (const auto& t : *all) {
                std::println("  [{}] {} - {} (etf={})", t.id, t.symbol,
                             t.company_name, t.is_etf);
            }
        }

        // find one
        std::println("");
        auto one = repo.find_by_symbol("AAPL");
        if (one) {
            std::println("Found: {} - {}", one->symbol, one->company_name);
        } else {
            std::println("Error: {}", one.error());
        }
    } catch (const std::exception& e) {
        std::println(stderr, "DB error: {}", e.what());
    }

    _exit(0);
}
