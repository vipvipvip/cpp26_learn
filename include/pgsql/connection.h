#pragma once

#include <pqxx/pqxx>
#include <string>

class Database {
public:
    Database();

    void list_tables();
    void show_table_columns(const std::string& table);

private:
    pqxx::connection conn_;
};
