#ifndef DATABASE_H
#define DATABASE_H

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <iostream>
#include "../../DataSources/DatabaseConnection.h"

class Database : public DatabaseConnection {
public:
    explicit Database(const std::string& dsn);
    ~Database();
    Database(const Database&) = delete;
    Database& operator = (const Database&) = delete;

    bool connect() override;
    bool disconnect() override;
    SQLHDBC getHDBC() const override;

private:
    bool verifyAndCreateTables();
    bool tableExists(const std::wstring& tableName);
    SQLHENV hEnv;
    SQLHDBC hDbc;
    bool connected;
    const std::string dsn;
};

#endif