#ifndef IREPOSITORIES_H
#define IREPOSITORIES_H

#include <vector>
#include <memory>
#include "../../Domain/Models/Shop.h"
#include "../../Domain/Models/Department.h"
#include "../../Domain/Models/Passport.h"
#include "../../Domain/Models/Product.h"
#include "../../Domain/Models/Employee.h"
#include "../../Domain/Models/InventoryItem.h"
#include "../../Domain/Models/Sale.h"

class IShopRepository {
public:
    virtual ~IShopRepository() = default;
    virtual std::shared_ptr<Shop> find(const Shop& model) = 0;
    virtual std::vector<std::shared_ptr<Shop>> findAll() = 0;
    virtual std::vector<std::shared_ptr<Shop>> findAllByProduct(const Product& model) = 0;
    virtual void add(const Shop& model) = 0;
    virtual void update(const Shop& model) = 0;
    virtual void remove(const Shop& model) = 0;
};

class IDepartmentRepository {
public:
    virtual ~IDepartmentRepository() = default;
    virtual std::shared_ptr<Department> find(const Department& model) = 0;
    virtual std::vector<std::shared_ptr<Department>> findAll() = 0;
    virtual void add(const Department& model) = 0;
    virtual void update(const Department& model) = 0;
    virtual void remove(const Department& model) = 0;
};

class IPassportRepository {
public:
    virtual ~IPassportRepository() = default;
    virtual std::shared_ptr<Passport> find(const Passport& model) = 0;
    virtual std::vector<std::shared_ptr<Passport>> findAll() = 0;
    virtual void add(const Passport& model) = 0;
    virtual void update(const Passport& model) = 0;
    virtual void remove(const Passport& model) = 0;
};

class IProductRepository {
public:
    virtual ~IProductRepository() = default;
    virtual std::shared_ptr<Product> find(const Product& model) = 0;
    virtual std::vector<std::shared_ptr<Product>> findAll() = 0;
    virtual std::vector<std::shared_ptr<Product>> findAllByShop(const Shop& model) = 0;
    virtual void add(const Product& model) = 0;
    virtual void update(const Product& model) = 0;
    virtual void remove(const Product& model) = 0;
};

class IEmployeeRepository {
public:
    virtual ~IEmployeeRepository() = default;
    virtual std::shared_ptr<Employee> find(const Employee& model) = 0;
    virtual std::vector<std::shared_ptr<Employee>> findAll() = 0;
    virtual void add(const Employee& model) = 0;
    virtual void update(const Employee& model) = 0;
    virtual void remove(const Employee& model) = 0;
};

class IInventoryItemRepository {
public:
    virtual ~IInventoryItemRepository() = default;
    virtual std::shared_ptr<InventoryItem> find(const InventoryItem& model) = 0;
    virtual std::vector<std::shared_ptr<InventoryItem>> findAll() = 0;
    virtual std::vector<std::shared_ptr<InventoryItem>> findAllByShop(const Shop& model) = 0;
    virtual void add(const InventoryItem& model) = 0;
    virtual void update(const InventoryItem& model) = 0;
    virtual void remove(const InventoryItem& model) = 0;
};

class ISaleRepository {
public:
    virtual ~ISaleRepository() = default;
    virtual std::shared_ptr<Sale> find(const Sale& model) = 0;
    virtual std::vector<std::shared_ptr<Sale>> findAll() = 0;
    virtual void add(const Sale& model) = 0;
    virtual void update(const Sale& model) = 0;
    virtual void remove(const Sale& model) = 0;
};

#endif