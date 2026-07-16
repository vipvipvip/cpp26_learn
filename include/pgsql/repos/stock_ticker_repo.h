#pragma once

#include "pgsql/db_pgsql.h"
#include "models/stock_ticker.h"

#include <expected>
#include <vector>

using DbError = std::string;

class StockTickerRepo {
public:
    explicit StockTickerRepo(DbPgsql& db);

    std::expected<StockTicker, DbError> find(int64_t id);
    std::expected<StockTicker, DbError> find_by_symbol(const std::string& symbol);
    std::expected<std::vector<StockTicker>, DbError> find_all();
    std::expected<StockTicker, DbError> insert(const StockTicker& ticker);
    std::expected<StockTicker, DbError> update(const StockTicker& ticker);
    std::expected<bool, DbError> remove(int64_t id);

private:
    DbPgsql& db_;
};
