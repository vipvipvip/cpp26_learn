#include "calculator.h"
#include "linalg/matrix.h"
#include "logger.h"
#include "pgsql/db_pgsql.h"
#include "pgsql/repos/stock_ticker_repo.h"
#include "reflection/reflect.h"
#include "simd/ops.h"
#include "std_execution/async.h"
#include "std_learn/transform.h"

#include <unistd.h>
#include <print>

int main() {
    std::println("=== C++26 Hands-On ===\n");

    //run_calculator_demo();
    // run_linalg_demo();
    // run_simd_demo();
    // run_execution_demo();
    // run_reflection_demo();
    run_std_tranform_demo();

    //log_stacktrace("main");

    std::println("\n=== PostgreSQL CRUD ===\n");

    try {
        DbPgsql db;
        StockTickerRepo repo(db);

        auto one = repo.find_by_symbol("AAPL");
        if (one) {
            std::println("Found: {} - {}", one->symbol, one->company_name);
        }
    } catch (const std::exception& e) {
        std::println(stderr, "DB error: {}", e.what());
    }

    _exit(0);
}
