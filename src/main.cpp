#include "calculator.h"
#include "logger.h"
#include "types.h"

#include <print>
#include <vector>

int main() {
    std::println("=== C++26 Hands-On ===\n");

    const std::vector<Command> commands = {
        {Op::Add, 10, 5},
        {Op::Sub, 10, 5},
        {Op::Mul, 10, 5},
        {Op::Div, 10, 5},
        //{Op::Div, 10, 0},  // error case
    };

    for (const auto& cmd : commands) {
        auto result = compute(cmd);
        log_result(cmd, result);
    }

    log_stacktrace("main");

    return 0;
}
