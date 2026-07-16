#pragma once

#include <cstdint>
#include <optional>
#include <string>

struct StockTicker {
    int64_t id{};
    std::string symbol;
    bool enabled{true};
    std::string company_name;
    bool is_etf{false};
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
};
