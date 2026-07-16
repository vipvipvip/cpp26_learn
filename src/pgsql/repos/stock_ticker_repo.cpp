#include "pgsql/repos/stock_ticker_repo.h"

#include <print>

namespace {
StockTicker row_to_ticker(const pqxx::row& row) {
    return StockTicker{
        .id = row[0].as<int64_t>(),
        .symbol = row[1].as<std::string>(),
        .enabled = row[2].as<bool>(),
        .company_name = row[3].as<std::string>(),
        .is_etf = row[4].as<bool>(),
        .created_at = row[5].is_null() ? std::nullopt : std::optional(row[5].as<std::string>()),
        .updated_at = row[6].is_null() ? std::nullopt : std::optional(row[6].as<std::string>()),
    };
}
}  // namespace

StockTickerRepo::StockTickerRepo(DbPgsql& db) : db_(db) {}

std::expected<StockTicker, DbError> StockTickerRepo::find(int64_t id) {
    pqxx::work txn(db_.conn());
    auto result = txn.exec(
        "SELECT id, symbol, enabled, company_name, is_etf, "
        "created_at::text, updated_at::text "
        "FROM tbl_stock_tickers WHERE id = " + txn.esc(std::to_string(id)));

    if (result.empty())
        return std::unexpected("ticker not found");

    return row_to_ticker(result[0]);
}

std::expected<StockTicker, DbError> StockTickerRepo::find_by_symbol(const std::string& symbol) {
    pqxx::work txn(db_.conn());
    auto result = txn.exec(
        "SELECT id, symbol, enabled, company_name, is_etf, "
        "created_at::text, updated_at::text "
        "FROM tbl_stock_tickers WHERE symbol = '" + txn.esc(symbol) + "'");

    if (result.empty())
        return std::unexpected("ticker not found: " + symbol);

    return row_to_ticker(result[0]);
}

std::expected<std::vector<StockTicker>, DbError> StockTickerRepo::find_all() {
    pqxx::work txn(db_.conn());
    auto result = txn.exec(
        "SELECT id, symbol, enabled, company_name, is_etf, "
        "created_at::text, updated_at::text "
        "FROM tbl_stock_tickers ORDER BY symbol");

    std::vector<StockTicker> tickers;
    tickers.reserve(result.size());

    for (const auto& row : result) {
        tickers.push_back(row_to_ticker(row));
    }

    return tickers;
}

std::expected<StockTicker, DbError> StockTickerRepo::insert(const StockTicker& ticker) {
    pqxx::work txn(db_.conn());
    pqxx::params params;
    params.append(ticker.symbol);
    params.append(ticker.enabled);
    params.append(ticker.company_name);
    params.append(ticker.is_etf);

    auto result = txn.exec(
        "INSERT INTO tbl_stock_tickers (symbol, enabled, company_name, is_etf) "
        "VALUES ($1, $2, $3, $4) "
        "RETURNING id, symbol, enabled, company_name, is_etf, "
        "created_at::text, updated_at::text",
        params);

    txn.commit();
    return row_to_ticker(result[0]);
}

std::expected<StockTicker, DbError> StockTickerRepo::update(const StockTicker& ticker) {
    pqxx::work txn(db_.conn());
    pqxx::params params;
    params.append(ticker.id);
    params.append(ticker.symbol);
    params.append(ticker.enabled);
    params.append(ticker.company_name);
    params.append(ticker.is_etf);

    auto result = txn.exec(
        "UPDATE tbl_stock_tickers "
        "SET symbol = $2, enabled = $3, company_name = $4, is_etf = $5, "
        "updated_at = NOW() "
        "WHERE id = $1 "
        "RETURNING id, symbol, enabled, company_name, is_etf, "
        "created_at::text, updated_at::text",
        params);

    txn.commit();

    if (result.empty())
        return std::unexpected("ticker not found");

    return row_to_ticker(result[0]);
}

std::expected<bool, DbError> StockTickerRepo::remove(int64_t id) {
    pqxx::work txn(db_.conn());
    pqxx::params params;
    params.append(id);

    auto result = txn.exec(
        "DELETE FROM tbl_stock_tickers WHERE id = $1", params);
    txn.commit();
    return result.affected_rows() > 0;
}
