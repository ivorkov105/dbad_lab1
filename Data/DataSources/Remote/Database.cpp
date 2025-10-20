#include "Database.h"
#include <windows.h>
#include <iostream>
#include <cwchar>
#include <map>
#include <vector>

Database::Database(const std::string& dsn): 
    hEnv(SQL_NULL_HENV), hDbc(SQL_NULL_HDBC), connected(false), dsn(dsn) {
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
}

Database::~Database() {
    disconnect();
    if (hEnv != SQL_NULL_HENV) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    }
}

bool Database::connect() {
    if (connected) return true;

    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    std::wstring wdsn(dsn.begin(), dsn.end());
    SQLWCHAR connStr[256];
    swprintf_s(connStr, sizeof(connStr) / sizeof(wchar_t), L"DSN=%s;", wdsn.c_str());
    SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    if (SQL_SUCCEEDED(ret)) {
        connected = true;
        std::wcout << L"Connection successful." << std::endl;
        std::wcout << L"Verifying database schema..." << std::endl;
        if (!verifyAndCreateTables()) {
            std::wcerr << L"Critical error: failed to initialize database schema." << std::endl;
            disconnect();
            return false;
        }
        std::wcout << L"Database schema is OK." << std::endl;
        return true;
    }
    else {
        SQLWCHAR sqlState[6], messageText[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;
        SQLGetDiagRecW(SQL_HANDLE_DBC, hDbc, 1, sqlState, &nativeError, messageText,
            sizeof(messageText) / sizeof(wchar_t), &textLength);

        std::wcerr << L"Connection failed." << std::endl;
        std::wcerr << L"SQLSTATE: " << sqlState << L", Message: " << messageText << std::endl;

        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        hDbc = SQL_NULL_HDBC;
        return false;
    }
}

bool Database::disconnect() {
    if (connected) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        hDbc = SQL_NULL_HDBC;
        connected = false;
        std::wcout << L"Disconnected." << std::endl;
        return true;
    }
    return false;
}

SQLHDBC Database::getHDBC() const {
    return hDbc;
}

bool Database::tableExists(const std::wstring& tableName) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    const wchar_t* query = L"SELECT to_regclass(?) IS NOT NULL";
    SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,
        tableName.length() * sizeof(wchar_t), 0, (SQLPOINTER)tableName.c_str(), 0, NULL);
    SQLExecute(hStmt);

    bool exists = false;
    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        short result = 0;
        SQLGetData(hStmt, 1, SQL_C_SHORT, &result, 0, NULL);
        if (result == 1) {
            exists = true;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return exists;
}

bool Database::verifyAndCreateTables() {
    const std::vector<std::pair<std::wstring, std::wstring>> tables = {
        {L"shops", LR"(
            CREATE TABLE shops (
                shop_id BIGSERIAL PRIMARY KEY,
                shop_name VARCHAR(255) NOT NULL,
                address VARCHAR(255) NOT NULL
            );
        )"},
        {L"departments", LR"(
            CREATE TABLE departments (
                department_id BIGSERIAL PRIMARY KEY,
                depart_name VARCHAR(255) NOT NULL UNIQUE
            );
        )"},
        {L"passports", LR"(
            CREATE TABLE passports (
                passport_id BIGSERIAL PRIMARY KEY,
                passport_num VARCHAR(50) NOT NULL UNIQUE,
                issue_date DATE NOT NULL,
                issuing_authority VARCHAR(255) NOT NULL
            );
        )"},
        {L"products", LR"(
            CREATE TABLE products (
                product_id BIGSERIAL PRIMARY KEY,
                prod_name VARCHAR(255) NOT NULL,
                unit VARCHAR(50) NOT NULL
            );
        )"},
        {L"employees", LR"(
            CREATE TABLE employees (
                employee_id BIGSERIAL PRIMARY KEY,
                last_name VARCHAR(100) NOT NULL,
                first_name VARCHAR(100) NOT NULL,
                middle_name VARCHAR(100),
                address VARCHAR(255) NOT NULL,
                birth_date DATE NOT NULL,
                passport_id BIGINT NOT NULL UNIQUE REFERENCES passports(passport_id),
                shop_id BIGINT NOT NULL REFERENCES shops(shop_id),
                department_id BIGINT NOT NULL REFERENCES departments(department_id)
            );
        )"},
        {L"inventory", LR"(
            CREATE TABLE inventory (
                shop_id BIGINT REFERENCES shops(shop_id) ON DELETE CASCADE,
                product_id BIGINT REFERENCES products(product_id) ON DELETE CASCADE,
                quantity NUMERIC(10, 3) NOT NULL CHECK (quantity >= 0),
                price NUMERIC(10, 2) NOT NULL CHECK (price > 0),
                PRIMARY KEY (shop_id, product_id)
            );
        )"},
        {L"sales", LR"(
            CREATE TABLE sales (
                sale_id BIGSERIAL PRIMARY KEY,
                sale_date TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
                shop_id BIGINT NOT NULL REFERENCES shops(shop_id),
                product_id BIGINT NOT NULL REFERENCES products(product_id),
                employee_id BIGINT NOT NULL REFERENCES employees(employee_id),
                quantity_sold NUMERIC(10, 3) NOT NULL CHECK (quantity_sold > 0)
            );
        )"}
    };

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    for (const auto& pair : tables) {
        const std::wstring& tableName = pair.first;
        const std::wstring& createQuery = pair.second;

        if (!tableExists(tableName)) {
            std::wcout << L"Table '" << tableName << L"' not found, creating..." << std::endl;

            SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)createQuery.c_str(), SQL_NTS);

            if (!SQL_SUCCEEDED(ret)) {
                SQLWCHAR sqlState[6], messageText[SQL_MAX_MESSAGE_LENGTH];
                SQLINTEGER nativeError;
                SQLSMALLINT textLength;
                SQLGetDiagRecW(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, messageText,
                    sizeof(messageText) / sizeof(wchar_t), &textLength);

                std::wcerr << L"Failed to create table '" << tableName << L"'." << std::endl;
                std::wcerr << L"SQLSTATE: " << sqlState << L", Message: " << messageText << std::endl;

                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                return false;
            }
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return true;
}