#include "logger.h"
#include "calculator.h"

#include <print>
#include <stacktrace>

void log_result(const Command& cmd, const CalcResult& result,
                std::source_location loc) {
    std::print("[{}:{}] ", loc.file_name(), loc.line());

    if (result) {
        std::println("{} {} {} = {}", cmd.lhs, op_name(cmd.op), cmd.rhs,
                     *result);
    } else {
        std::println("ERROR: {} {} {} -> {}", cmd.lhs, op_name(cmd.op),
                     cmd.rhs, result.error());
    }
}

void log_stacktrace(std::string_view label) {
    std::print("--- {} stacktrace ---\n", label);
    std::print("{}", std::stacktrace::current());
    std::print("--- end ---\n");
}
