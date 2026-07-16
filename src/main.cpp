#include "calculator.h"
#include "logger.h"
#include "pgsql/connection.h"

#include <unistd.h>
#include <print>

int main() {
    std::println("=== C++26 Hands-On ===\n");

    run_calculator_demo();
    log_stacktrace("main");

    std::println("\n=== PostgreSQL ===\n");

    try {
        Database db;
        db.list_tables();
    } catch (const std::exception& e) {
        std::println(stderr, "DB error: {}", e.what());
    }

    _exit(0);
}
