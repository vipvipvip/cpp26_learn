#pragma once

#include <execution>
#include <string>
#include <vector>

struct Trade {
    int64_t id;
    std::string symbol;
    double price;
    int quantity;
};

void run_execution_demo();
