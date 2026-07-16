#include "pgsql/connection.h"

#include <iostream>
#include <print>

Database::Database()
    : conn_("host=127.0.0.1 port=5432 dbname=swingtrader user=swingtrader password=swingtrader_dev_password") {
    std::println("Connected to: {}", conn_.dbname());
}

void Database::list_tables() {
    pqxx::work txn(conn_);

    auto result = txn.exec(
        "SELECT table_schema, table_name, table_type "
        "FROM information_schema.tables "
        "WHERE table_schema NOT IN ('pg_catalog', 'information_schema') "
        "ORDER BY table_schema, table_name");

    std::println("\n--- Tables ---");
    for (const auto& row : result) {
        std::println("  {}.{} [{}]", row[0].c_str(), row[1].c_str(),
                     row[2].c_str());
    }
    std::println("  ({} tables)\n", result.size());
}

void Database::show_table_columns(const std::string& table) {
    pqxx::work txn(conn_);

    auto result = txn.exec(
        "SELECT column_name, data_type, is_nullable "
        "FROM information_schema.columns "
        "WHERE table_name = '" + txn.esc(table) + "' "
        "ORDER BY ordinal_position");

    if (result.empty()) {
        std::println("Table '{}' not found.", table);
        return;
    }

    std::println("--- Columns: {} ---", table);
    for (const auto& row : result) {
        std::println("  {:<30} {:<20} {}", row[0].c_str(), row[1].c_str(),
                     row[2].c_str());
    }
}
