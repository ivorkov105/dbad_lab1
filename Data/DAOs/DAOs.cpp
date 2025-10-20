#include "DAOs.h"
#include <stdexcept>
#include <windows.h>
#include <sqlext.h>
#include <string>
#include <vector>

static void handleOdbcError(SQLRETURN ret, SQLSMALLINT handleType, SQLHANDLE handle) {
    if (!SQL_SUCCEEDED(ret)) {
        if (handleType == SQL_HANDLE_STMT) SQLFreeHandle(SQL_HANDLE_STMT, handle);
        throw std::runtime_error("ODBC Error");
    }
}

ShopDAO::ShopDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<ShopEntity> ShopDAO::findById(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT shop_id, shop_name, address FROM shops WHERE shop_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<ShopEntity>();
        long long eId;
        wchar_t name[256];
        wchar_t address[256];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &indicator);
        SQLGetData(hStmt, 3, SQL_C_WCHAR, address, sizeof(address), &indicator);

        entity->setId(eId);
        entity->setName(name);
        entity->setAddress(address);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<ShopEntity>> ShopDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<ShopEntity>> result;
    const wchar_t* query = L"SELECT shop_id, shop_name, address FROM shops ORDER BY shop_id";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<ShopEntity>();
        long long eId;
        wchar_t name[256];
        wchar_t address[256];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &indicator);
        SQLGetData(hStmt, 3, SQL_C_WCHAR, address, sizeof(address), &indicator);

        entity->setId(eId);
        entity->setName(name);
        entity->setAddress(address);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void ShopDAO::add(const ShopEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO shops (shop_name, address) VALUES (?, ?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& name = entity.getName();
    const std::wstring& address = entity.getAddress();
    SQLLEN nameLen = name.size() * sizeof(wchar_t);
    SQLLEN addrLen = address.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, name.size(), 0, (SQLPOINTER)name.c_str(), 0, &nameLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, address.size(), 0, (SQLPOINTER)address.c_str(), 0, &addrLen);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void ShopDAO::update(const ShopEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE shops SET shop_name = ?, address = ? WHERE shop_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& name = entity.getName();
    const std::wstring& address = entity.getAddress();
    long long id = entity.getId();
    SQLLEN nameLen = name.size() * sizeof(wchar_t);
    SQLLEN addrLen = address.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, name.size(), 0, (SQLPOINTER)name.c_str(), 0, &nameLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, address.size(), 0, (SQLPOINTER)address.c_str(), 0, &addrLen);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void ShopDAO::remove(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM shops WHERE shop_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

DepartmentDAO::DepartmentDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<DepartmentEntity> DepartmentDAO::findById(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT department_id, depart_name FROM departments WHERE department_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<DepartmentEntity>();
        long long eId;
        wchar_t name[256];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &indicator);

        entity->setId(eId);
        entity->setName(name);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<DepartmentEntity>> DepartmentDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<DepartmentEntity>> result;
    const wchar_t* query = L"SELECT department_id, depart_name FROM departments ORDER BY department_id";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<DepartmentEntity>();
        long long eId;
        wchar_t name[256];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &indicator);

        entity->setId(eId);
        entity->setName(name);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void DepartmentDAO::add(const DepartmentEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO departments (depart_name) VALUES (?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& name = entity.getName();
    SQLLEN nameLen = name.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, name.size(), 0, (SQLPOINTER)name.c_str(), 0, &nameLen);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void DepartmentDAO::update(const DepartmentEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE departments SET depart_name = ? WHERE department_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& name = entity.getName();
    long long id = entity.getId();
    SQLLEN nameLen = name.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, name.size(), 0, (SQLPOINTER)name.c_str(), 0, &nameLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void DepartmentDAO::remove(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM departments WHERE department_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

PassportDAO::PassportDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<PassportEntity> PassportDAO::findById(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT passport_id, passport_num, issue_date, issuing_authority FROM passports WHERE passport_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<PassportEntity>();
        long long eId;
        wchar_t num[51];
        SQL_DATE_STRUCT date;
        wchar_t auth[256];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, num, sizeof(num), &indicator);
        SQLGetData(hStmt, 3, SQL_C_TYPE_DATE, &date, sizeof(date), &indicator);
        SQLGetData(hStmt, 4, SQL_C_WCHAR, auth, sizeof(auth), &indicator);

        entity->setId(eId);
        entity->setPassportNumber(num);
        entity->setIssueDate(date);
        entity->setIssuingAuthority(auth);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<PassportEntity>> PassportDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<PassportEntity>> result;
    const wchar_t* query = L"SELECT passport_id, passport_num, issue_date, issuing_authority FROM passports ORDER BY passport_id";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<PassportEntity>();
        long long eId;
        wchar_t num[51];
        SQL_DATE_STRUCT date;
        wchar_t auth[256];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, num, sizeof(num), &indicator);
        SQLGetData(hStmt, 3, SQL_C_TYPE_DATE, &date, sizeof(date), &indicator);
        SQLGetData(hStmt, 4, SQL_C_WCHAR, auth, sizeof(auth), &indicator);

        entity->setId(eId);
        entity->setPassportNumber(num);
        entity->setIssueDate(date);
        entity->setIssuingAuthority(auth);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void PassportDAO::add(const PassportEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO passports (passport_num, issue_date, issuing_authority) VALUES (?, ?, ?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& num = entity.getPassportNumber();
    const std::wstring& auth = entity.getIssuingAuthority();
    SQL_DATE_STRUCT date = entity.getIssueDate();
    SQLLEN numLen = num.size() * sizeof(wchar_t);
    SQLLEN authLen = auth.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, num.size(), 0, (SQLPOINTER)num.c_str(), 0, &numLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &date, 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, auth.size(), 0, (SQLPOINTER)auth.c_str(), 0, &authLen);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void PassportDAO::update(const PassportEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE passports SET passport_num = ?, issue_date = ?, issuing_authority = ? WHERE passport_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long id = entity.getId();
    const std::wstring& num = entity.getPassportNumber();
    const std::wstring& auth = entity.getIssuingAuthority();
    SQL_DATE_STRUCT date = entity.getIssueDate();
    SQLLEN numLen = num.size() * sizeof(wchar_t);
    SQLLEN authLen = auth.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, num.size(), 0, (SQLPOINTER)num.c_str(), 0, &numLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &date, 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, auth.size(), 0, (SQLPOINTER)auth.c_str(), 0, &authLen);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void PassportDAO::remove(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM passports WHERE passport_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

ProductDAO::ProductDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<ProductEntity> ProductDAO::findById(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT product_id, prod_name, unit FROM products WHERE product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<ProductEntity>();
        long long eId;
        wchar_t name[256];
        wchar_t unit[51];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &indicator);
        SQLGetData(hStmt, 3, SQL_C_WCHAR, unit, sizeof(unit), &indicator);

        entity->setId(eId);
        entity->setProdName(name);
        entity->setUnit(unit);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<ProductEntity>> ProductDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<ProductEntity>> result;
    const wchar_t* query = L"SELECT product_id, prod_name, unit FROM products ORDER BY product_id";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<ProductEntity>();
        long long eId;
        wchar_t name[256];
        wchar_t unit[51];
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &indicator);
        SQLGetData(hStmt, 3, SQL_C_WCHAR, unit, sizeof(unit), &indicator);

        entity->setId(eId);
        entity->setProdName(name);
        entity->setUnit(unit);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void ProductDAO::add(const ProductEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO products (prod_name, unit) VALUES (?, ?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& name = entity.getProdName();
    const std::wstring& unit = entity.getUnit();
    SQLLEN nameLen = name.size() * sizeof(wchar_t);
    SQLLEN unitLen = unit.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, name.size(), 0, (SQLPOINTER)name.c_str(), 0, &nameLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, unit.size(), 0, (SQLPOINTER)unit.c_str(), 0, &unitLen);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void ProductDAO::update(const ProductEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE products SET prod_name = ?, unit = ? WHERE product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long id = entity.getId();
    const std::wstring& name = entity.getProdName();
    const std::wstring& unit = entity.getUnit();
    SQLLEN nameLen = name.size() * sizeof(wchar_t);
    SQLLEN unitLen = unit.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, name.size(), 0, (SQLPOINTER)name.c_str(), 0, &nameLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, unit.size(), 0, (SQLPOINTER)unit.c_str(), 0, &unitLen);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void ProductDAO::remove(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM products WHERE product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

EmployeeDAO::EmployeeDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<EmployeeEntity> EmployeeDAO::findById(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT employee_id, last_name, first_name, middle_name, address, birth_date, passport_id, shop_id, department_id FROM employees WHERE employee_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<EmployeeEntity>();
        long long eId, pId, sId, dId;
        wchar_t ln[101], fn[101], mn[101], addr[256];
        SQL_DATE_STRUCT bDate;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, ln, sizeof(ln), &indicator);
        SQLGetData(hStmt, 3, SQL_C_WCHAR, fn, sizeof(fn), &indicator);
        SQLGetData(hStmt, 4, SQL_C_WCHAR, mn, sizeof(mn), &indicator);
        SQLGetData(hStmt, 5, SQL_C_WCHAR, addr, sizeof(addr), &indicator);
        SQLGetData(hStmt, 6, SQL_C_TYPE_DATE, &bDate, 0, &indicator);
        SQLGetData(hStmt, 7, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 8, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 9, SQL_C_SBIGINT, &dId, 0, &indicator);

        entity->setId(eId);
        entity->setLastName(ln);
        entity->setFirstName(fn);
        entity->setMiddleName(mn);
        entity->setAddress(addr);
        entity->setBirthDate(bDate);
        entity->setPassportId(pId);
        entity->setShopId(sId);
        entity->setDepartmentId(dId);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<EmployeeEntity>> EmployeeDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<EmployeeEntity>> result;
    const wchar_t* query = L"SELECT employee_id, last_name, first_name, middle_name, address, birth_date, passport_id, shop_id, department_id FROM employees ORDER BY employee_id";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<EmployeeEntity>();
        long long eId, pId, sId, dId;
        wchar_t ln[101], fn[101], mn[101], addr[256];
        SQL_DATE_STRUCT bDate;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_WCHAR, ln, sizeof(ln), &indicator);
        SQLGetData(hStmt, 3, SQL_C_WCHAR, fn, sizeof(fn), &indicator);
        SQLGetData(hStmt, 4, SQL_C_WCHAR, mn, sizeof(mn), &indicator);
        SQLGetData(hStmt, 5, SQL_C_WCHAR, addr, sizeof(addr), &indicator);
        SQLGetData(hStmt, 6, SQL_C_TYPE_DATE, &bDate, 0, &indicator);
        SQLGetData(hStmt, 7, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 8, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 9, SQL_C_SBIGINT, &dId, 0, &indicator);

        entity->setId(eId);
        entity->setLastName(ln);
        entity->setFirstName(fn);
        entity->setMiddleName(mn);
        entity->setAddress(addr);
        entity->setBirthDate(bDate);
        entity->setPassportId(pId);
        entity->setShopId(sId);
        entity->setDepartmentId(dId);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void EmployeeDAO::add(const EmployeeEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO employees (last_name, first_name, middle_name, address, birth_date, passport_id, shop_id, department_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    const std::wstring& ln = entity.getLastName();
    const std::wstring& fn = entity.getFirstName();
    const std::wstring& mn = entity.getMiddleName();
    const std::wstring& addr = entity.getAddress();
    SQL_DATE_STRUCT bDate = entity.getBirthDate();
    long long pId = entity.getPassportId();
    long long sId = entity.getShopId();
    long long dId = entity.getDepartmentId();

    SQLLEN lnLen = ln.size() * sizeof(wchar_t);
    SQLLEN fnLen = fn.size() * sizeof(wchar_t);
    SQLLEN mnLen = mn.size() * sizeof(wchar_t);
    SQLLEN addrLen = addr.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, ln.size(), 0, (SQLPOINTER)ln.c_str(), 0, &lnLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, fn.size(), 0, (SQLPOINTER)fn.c_str(), 0, &fnLen);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, mn.size(), 0, (SQLPOINTER)mn.c_str(), 0, &mnLen);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, addr.size(), 0, (SQLPOINTER)addr.c_str(), 0, &addrLen);
    SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &bDate, 0, NULL);
    SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pId, 0, NULL);
    SQLBindParameter(hStmt, 7, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &sId, 0, NULL);
    SQLBindParameter(hStmt, 8, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &dId, 0, NULL);

    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void EmployeeDAO::update(const EmployeeEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE employees SET last_name=?, first_name=?, middle_name=?, address=?, birth_date=?, passport_id=?, shop_id=?, department_id=? WHERE employee_id=?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long id = entity.getId();
    const std::wstring& ln = entity.getLastName();
    const std::wstring& fn = entity.getFirstName();
    const std::wstring& mn = entity.getMiddleName();
    const std::wstring& addr = entity.getAddress();
    SQL_DATE_STRUCT bDate = entity.getBirthDate();
    long long pId = entity.getPassportId();
    long long sId = entity.getShopId();
    long long dId = entity.getDepartmentId();

    SQLLEN lnLen = ln.size() * sizeof(wchar_t);
    SQLLEN fnLen = fn.size() * sizeof(wchar_t);
    SQLLEN mnLen = mn.size() * sizeof(wchar_t);
    SQLLEN addrLen = addr.size() * sizeof(wchar_t);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, ln.size(), 0, (SQLPOINTER)ln.c_str(), 0, &lnLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, fn.size(), 0, (SQLPOINTER)fn.c_str(), 0, &fnLen);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, mn.size(), 0, (SQLPOINTER)mn.c_str(), 0, &mnLen);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, addr.size(), 0, (SQLPOINTER)addr.c_str(), 0, &addrLen);
    SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &bDate, 0, NULL);
    SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pId, 0, NULL);
    SQLBindParameter(hStmt, 7, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &sId, 0, NULL);
    SQLBindParameter(hStmt, 8, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &dId, 0, NULL);
    SQLBindParameter(hStmt, 9, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);

    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void EmployeeDAO::remove(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM employees WHERE employee_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

InventoryItemDAO::InventoryItemDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<InventoryItemEntity> InventoryItemDAO::findById(long long shopId, long long productId) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT shop_id, product_id, quantity, price FROM inventory WHERE shop_id = ? AND product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &shopId, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &productId, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<InventoryItemEntity>();
        long long sId, pId;
        double quant, pr;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 3, SQL_C_DOUBLE, &quant, 0, &indicator);
        SQLGetData(hStmt, 4, SQL_C_DOUBLE, &pr, 0, &indicator);

        entity->setShopId(sId);
        entity->setProductId(pId);
        entity->setQuantity(quant);
        entity->setPrice(pr);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<InventoryItemEntity>> InventoryItemDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<InventoryItemEntity>> result;
    const wchar_t* query = L"SELECT shop_id, product_id, quantity, price FROM inventory";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<InventoryItemEntity>();
        long long sId, pId;
        double quant, pr;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 3, SQL_C_DOUBLE, &quant, 0, &indicator);
        SQLGetData(hStmt, 4, SQL_C_DOUBLE, &pr, 0, &indicator);

        entity->setShopId(sId);
        entity->setProductId(pId);
        entity->setQuantity(quant);
        entity->setPrice(pr);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

std::vector<std::shared_ptr<InventoryItemEntity>> InventoryItemDAO::findAllByShopId(long long shopId) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<InventoryItemEntity>> result;
    const wchar_t* query = L"SELECT shop_id, product_id, quantity, price FROM inventory WHERE shop_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &shopId, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<InventoryItemEntity>();
        long long sId, pId;
        double quant, pr;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 3, SQL_C_DOUBLE, &quant, 0, &indicator);
        SQLGetData(hStmt, 4, SQL_C_DOUBLE, &pr, 0, &indicator);

        entity->setShopId(sId);
        entity->setProductId(pId);
        entity->setQuantity(quant);
        entity->setPrice(pr);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

std::vector<std::shared_ptr<InventoryItemEntity>> InventoryItemDAO::findAllByProductId(long long productId) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<InventoryItemEntity>> result;
    const wchar_t* query = L"SELECT shop_id, product_id, quantity, price FROM inventory WHERE product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &productId, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<InventoryItemEntity>();
        long long sId, pId;
        double quant, pr;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 3, SQL_C_DOUBLE, &quant, 0, &indicator);
        SQLGetData(hStmt, 4, SQL_C_DOUBLE, &pr, 0, &indicator);

        entity->setShopId(sId);
        entity->setProductId(pId);
        entity->setQuantity(quant);
        entity->setPrice(pr);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void InventoryItemDAO::add(const InventoryItemEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO inventory (shop_id, product_id, quantity, price) VALUES (?, ?, ?, ?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long shopId = entity.getShopId();
    long long productId = entity.getProductId();
    double quantity = entity.getQuantity();
    double price = entity.getPrice();

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &shopId, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &productId, 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 3, &quantity, 0, NULL);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2, &price, 0, NULL);

    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void InventoryItemDAO::update(const InventoryItemEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE inventory SET quantity = ?, price = ? WHERE shop_id = ? AND product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long shopId = entity.getShopId();
    long long productId = entity.getProductId();
    double quantity = entity.getQuantity();
    double price = entity.getPrice();

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 3, &quantity, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2, &price, 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &shopId, 0, NULL);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &productId, 0, NULL);

    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void InventoryItemDAO::remove(long long shopId, long long productId) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM inventory WHERE shop_id = ? AND product_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &shopId, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &productId, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

SaleDAO::SaleDAO(std::shared_ptr<DatabaseConnection> dbConn) : db(dbConn) {}

std::shared_ptr<SaleEntity> SaleDAO::findById(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"SELECT sale_id, sale_date, shop_id, product_id, employee_id, quantity_sold FROM sales WHERE sale_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);

    if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<SaleEntity>();
        long long eId, sId, pId, empId;
        SQL_TIMESTAMP_STRUCT sDate;
        double quant;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_TYPE_TIMESTAMP, &sDate, sizeof(sDate), &indicator);
        SQLGetData(hStmt, 3, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 4, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 5, SQL_C_SBIGINT, &empId, 0, &indicator);
        SQLGetData(hStmt, 6, SQL_C_DOUBLE, &quant, 0, &indicator);

        entity->setId(eId);
        entity->setSaleDate(sDate);
        entity->setShopId(sId);
        entity->setProductId(pId);
        entity->setEmployeeId(empId);
        entity->setQuantitySold(quant);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return entity;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return nullptr;
}

std::vector<std::shared_ptr<SaleEntity>> SaleDAO::findAll() {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    std::vector<std::shared_ptr<SaleEntity>> result;
    const wchar_t* query = L"SELECT sale_id, sale_date, shop_id, product_id, employee_id, quantity_sold FROM sales ORDER BY sale_id";
    handleOdbcError(SQLExecDirectW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
        auto entity = std::make_shared<SaleEntity>();
        long long eId, sId, pId, empId;
        SQL_TIMESTAMP_STRUCT sDate;
        double quant;
        SQLLEN indicator;

        SQLGetData(hStmt, 1, SQL_C_SBIGINT, &eId, 0, &indicator);
        SQLGetData(hStmt, 2, SQL_C_TYPE_TIMESTAMP, &sDate, sizeof(sDate), &indicator);
        SQLGetData(hStmt, 3, SQL_C_SBIGINT, &sId, 0, &indicator);
        SQLGetData(hStmt, 4, SQL_C_SBIGINT, &pId, 0, &indicator);
        SQLGetData(hStmt, 5, SQL_C_SBIGINT, &empId, 0, &indicator);
        SQLGetData(hStmt, 6, SQL_C_DOUBLE, &quant, 0, &indicator);

        entity->setId(eId);
        entity->setSaleDate(sDate);
        entity->setShopId(sId);
        entity->setProductId(pId);
        entity->setEmployeeId(empId);
        entity->setQuantitySold(quant);
        result.push_back(entity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return result;
}

void SaleDAO::add(const SaleEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"INSERT INTO sales (shop_id, product_id, employee_id, quantity_sold) VALUES (?, ?, ?, ?)";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long sId = entity.getShopId();
    long long pId = entity.getProductId();
    long long empId = entity.getEmployeeId();
    double quant = entity.getQuantitySold();

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &sId, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pId, 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &empId, 0, NULL);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 3, &quant, 0, NULL);

    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void SaleDAO::update(const SaleEntity& entity) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"UPDATE sales SET shop_id=?, product_id=?, employee_id=?, quantity_sold=? WHERE sale_id=?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);

    long long id = entity.getId();
    long long sId = entity.getShopId();
    long long pId = entity.getProductId();
    long long empId = entity.getEmployeeId();
    double quant = entity.getQuantitySold();

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &sId, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pId, 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &empId, 0, NULL);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 3, &quant, 0, NULL);
    SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);

    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void SaleDAO::remove(long long id) {
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db->getHDBC(), &hStmt);
    const wchar_t* query = L"DELETE FROM sales WHERE sale_id = ?";
    handleOdbcError(SQLPrepareW(hStmt, (SQLWCHAR*)query, SQL_NTS), SQL_HANDLE_STMT, hStmt);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &id, 0, NULL);
    handleOdbcError(SQLExecute(hStmt), SQL_HANDLE_STMT, hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}