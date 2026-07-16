#pragma once

#include <pqxx/pqxx>
#include <string>

class DbPgsql {
public:
    DbPgsql();

    void list_tables();
    void show_table_columns(const std::string& table);

private:
    pqxx::connection conn_;
};
