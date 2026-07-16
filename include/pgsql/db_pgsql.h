#pragma once

#include <pqxx/pqxx>
#include <string>

class DbPgsql {
public:
    DbPgsql();

    void list_tables();
    void show_table_columns(const std::string& table);

    pqxx::connection& conn() { return conn_; }
    pqxx::connection conn_;
};
