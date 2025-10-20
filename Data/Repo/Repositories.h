#ifndef REPOSITORIES_H
#define REPOSITORIES_H

#include "../../Domain/Repo/IRepositories.h"
#include "../DataMappers/DataMappers.h"
#include "../DAOs/DAOs.h"
#include "../../Domain/LocalStorage/DataContainer.h"
#include <memory>

class ShopRepository : public IShopRepository {
public:
    explicit ShopRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<ShopMapper> mapper, std::shared_ptr<ShopDAO> dao, std::shared_ptr<InventoryItemDAO> invDao);
    std::shared_ptr<Shop> find(const Shop& model) override;
    std::vector<std::shared_ptr<Shop>> findAll() override;
    std::vector<std::shared_ptr<Shop>> findAllByProduct(const Product& model) override;
    void add(const Shop& model) override;
    void update(const Shop& model) override;
    void remove(const Shop& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<ShopMapper> mapper;
    std::shared_ptr<ShopDAO> dao;
    std::shared_ptr<InventoryItemDAO> invDao;
};

class DepartmentRepository : public IDepartmentRepository {
public:
    explicit DepartmentRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<DepartmentMapper> mapper, std::shared_ptr<DepartmentDAO> dao);
    std::shared_ptr<Department> find(const Department& model) override;
    std::vector<std::shared_ptr<Department>> findAll() override;
    void add(const Department& model) override;
    void update(const Department& model) override;
    void remove(const Department& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<DepartmentMapper> mapper;
    std::shared_ptr<DepartmentDAO> dao;
};

class PassportRepository : public IPassportRepository {
public:
    explicit PassportRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<PassportMapper> mapper, std::shared_ptr<PassportDAO> dao);
    std::shared_ptr<Passport> find(const Passport& model) override;
    std::vector<std::shared_ptr<Passport>> findAll() override;
    void add(const Passport& model) override;
    void update(const Passport& model) override;
    void remove(const Passport& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<PassportMapper> mapper;
    std::shared_ptr<PassportDAO> dao;
};

class ProductRepository : public IProductRepository {
public:
    explicit ProductRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<ProductMapper> mapper, std::shared_ptr<ProductDAO> dao, std::shared_ptr<InventoryItemDAO> invDao);
    std::shared_ptr<Product> find(const Product& model) override;
    std::vector<std::shared_ptr<Product>> findAll() override;
    std::vector<std::shared_ptr<Product>> findAllByShop(const Shop& model) override;
    void add(const Product& model) override;
    void update(const Product& model) override;
    void remove(const Product& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<ProductMapper> mapper;
    std::shared_ptr<ProductDAO> dao;
    std::shared_ptr<InventoryItemDAO> invDao;
};

class EmployeeRepository : public IEmployeeRepository {
public:
    explicit EmployeeRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<EmployeeMapper> mapper, std::shared_ptr<EmployeeDAO> dao);
    std::shared_ptr<Employee> find(const Employee& model) override;
    std::vector<std::shared_ptr<Employee>> findAll() override;
    void add(const Employee& model) override;
    void update(const Employee& model) override;
    void remove(const Employee& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<EmployeeMapper> mapper;
    std::shared_ptr<EmployeeDAO> dao;
};

class InventoryItemRepository : public IInventoryItemRepository {
public:
    explicit InventoryItemRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<InventoryItemMapper> mapper, std::shared_ptr<InventoryItemDAO> dao);
    std::shared_ptr<InventoryItem> find(const InventoryItem& model) override;
    std::vector<std::shared_ptr<InventoryItem>> findAll() override;
    std::vector<std::shared_ptr<InventoryItem>> findAllByShop(const Shop& model) override;
    void add(const InventoryItem& model) override;
    void update(const InventoryItem& model) override;
    void remove(const InventoryItem& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<InventoryItemMapper> mapper;
    std::shared_ptr<InventoryItemDAO> dao;
};

class SaleRepository : public ISaleRepository {
public:
    explicit SaleRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<SaleMapper> mapper, std::shared_ptr<SaleDAO> dao);
    std::shared_ptr<Sale> find(const Sale& model) override;
    std::vector<std::shared_ptr<Sale>> findAll() override;
    void add(const Sale& model) override;
    void update(const Sale& model) override;
    void remove(const Sale& model) override;
private:
    std::shared_ptr<DataContainer> dataContainer;
    std::shared_ptr<SaleMapper> mapper;
    std::shared_ptr<SaleDAO> dao;
};

#endif