#ifndef DAOS_H
#define DAOS_H

#include <vector>
#include <memory>
#include "../DataSources/DatabaseConnection.h"
#include "../Entities/ShopEntity.h"
#include "../Entities/DepartmentEntity.h"
#include "../Entities/PassportEntity.h"
#include "../Entities/ProductEntity.h"
#include "../Entities/EmployeeEntity.h"
#include "../Entities/InventoryItemEntity.h"
#include "../Entities/SaleEntity.h"

class ShopDAO {
public:
    explicit ShopDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<ShopEntity> findById(long long id);
    std::vector<std::shared_ptr<ShopEntity>> findAll();
    void add(const ShopEntity& entity);
    void update(const ShopEntity& entity);
    void remove(long long id);
private:
    std::shared_ptr<DatabaseConnection> db;
};

class DepartmentDAO {
public:
    explicit DepartmentDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<DepartmentEntity> findById(long long id);
    std::vector<std::shared_ptr<DepartmentEntity>> findAll();
    void add(const DepartmentEntity& entity);
    void update(const DepartmentEntity& entity);
    void remove(long long id);
private:
    std::shared_ptr<DatabaseConnection> db;
};

class PassportDAO {
public:
    explicit PassportDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<PassportEntity> findById(long long id);
    std::vector<std::shared_ptr<PassportEntity>> findAll();
    void add(const PassportEntity& entity);
    void update(const PassportEntity& entity);
    void remove(long long id);
private:
    std::shared_ptr<DatabaseConnection> db;
};

class ProductDAO {
public:
    explicit ProductDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<ProductEntity> findById(long long id);
    std::vector<std::shared_ptr<ProductEntity>> findAll();
    void add(const ProductEntity& entity);
    void update(const ProductEntity& entity);
    void remove(long long id);
private:
    std::shared_ptr<DatabaseConnection> db;
};

class EmployeeDAO {
public:
    explicit EmployeeDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<EmployeeEntity> findById(long long id);
    std::vector<std::shared_ptr<EmployeeEntity>> findAll();
    void add(const EmployeeEntity& entity);
    void update(const EmployeeEntity& entity);
    void remove(long long id);
private:
    std::shared_ptr<DatabaseConnection> db;
};

class InventoryItemDAO {
public:
    explicit InventoryItemDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<InventoryItemEntity> findById(long long shopId, long long productId);
    std::vector<std::shared_ptr<InventoryItemEntity>> findAll();
    std::vector<std::shared_ptr<InventoryItemEntity>> findAllByShopId(long long shopId);
    std::vector<std::shared_ptr<InventoryItemEntity>> findAllByProductId(long long productId);
    void add(const InventoryItemEntity& entity);
    void update(const InventoryItemEntity& entity);
    void remove(long long shopId, long long productId);
private:
    std::shared_ptr<DatabaseConnection> db;
};

class SaleDAO {
public:
    explicit SaleDAO(std::shared_ptr<DatabaseConnection> dbConnection);
    std::shared_ptr<SaleEntity> findById(long long id);
    std::vector<std::shared_ptr<SaleEntity>> findAll();
    void add(const SaleEntity& entity);
    void update(const SaleEntity& entity);
    void remove(long long id);
private:
    std::shared_ptr<DatabaseConnection> db;
};

#endif