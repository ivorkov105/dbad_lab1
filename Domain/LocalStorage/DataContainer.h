#ifndef DATA_CONTAINER_H
#define DATA_CONTAINER_H

#include <vector>
#include <memory>
#include <map>
#include <utility>
#include "../../Domain/Models/Department.h"
#include "../../Domain/Models/Employee.h"
#include "../../Domain/Models/InventoryItem.h"
#include "../../Domain/Models/Passport.h"
#include "../../Domain/Models/Product.h"
#include "../../Domain/Models/Sale.h"
#include "../../Domain/Models/Shop.h"

class DataContainer {
private:
    std::vector<std::shared_ptr<Department>> departments;
    std::vector<std::shared_ptr<Employee>> employees;
    std::vector<std::shared_ptr<InventoryItem>> inventoryItems;
    std::vector<std::shared_ptr<Passport>> passports;
    std::vector<std::shared_ptr<Product>> products;
    std::vector<std::shared_ptr<Sale>> sales;
    std::vector<std::shared_ptr<Shop>> shops;

    std::map<long long, std::shared_ptr<Department>> departmentMap;
    std::map<long long, std::shared_ptr<Employee>> employeeMap;
    std::map<std::pair<long long, long long>, std::shared_ptr<InventoryItem>> invItemMap;
    std::map<long long, std::shared_ptr<Passport>> passportMap;
    std::map<long long, std::shared_ptr<Product>> productMap;
    std::map<long long, std::shared_ptr<Sale>> saleMap;
    std::map<long long, std::shared_ptr<Shop>> shopMap;

public:
    DataContainer();

    void addDepartment(std::shared_ptr<Department> model);
    std::shared_ptr<Department> findDepartmentById(long long id);
    std::vector<std::shared_ptr<Department>> getAllDepartments();
    void updateDepartment(std::shared_ptr<Department> model);
    void removeDepartment(long long id);

    void addEmployee(std::shared_ptr<Employee> model);
    std::shared_ptr<Employee> findEmployeeById(long long id);
    std::vector<std::shared_ptr<Employee>> getAllEmployees();
    void updateEmployee(std::shared_ptr<Employee> model);
    void removeEmployee(long long id);

    void addInventoryItem(std::shared_ptr<InventoryItem> model);
    std::shared_ptr<InventoryItem> findInventoryItemByIds(long long shopId, long long productId);
    std::vector<std::shared_ptr<InventoryItem>> getAllInventoryItems();
    std::vector<std::shared_ptr<InventoryItem>> findAllInventoryItemsByShopId(long long shopId);
    std::vector<std::shared_ptr<InventoryItem>> findAllInventoryItemsByProductId(long long productId);
    void updateInventoryItem(std::shared_ptr<InventoryItem> model);
    void removeInventoryItem(long long shopId, long long productId);

    void addPassport(std::shared_ptr<Passport> model);
    std::shared_ptr<Passport> findPassportById(long long id);
    std::vector<std::shared_ptr<Passport>> getAllPassports();
    void updatePassport(std::shared_ptr<Passport> model);
    void removePassport(long long id);

    void addProduct(std::shared_ptr<Product> model);
    std::shared_ptr<Product> findProductById(long long id);
    std::vector<std::shared_ptr<Product>> getAllProducts();
    void updateProduct(std::shared_ptr<Product> model);
    void removeProduct(long long id);

    void addSale(std::shared_ptr<Sale> model);
    std::shared_ptr<Sale> findSaleById(long long id);
    std::vector<std::shared_ptr<Sale>> getAllSales();
    void updateSale(std::shared_ptr<Sale> model);
    void removeSale(long long id);

    void addShop(std::shared_ptr<Shop> model);
    std::shared_ptr<Shop> findShopById(long long id);
    std::vector<std::shared_ptr<Shop>> getAllShops();
    void updateShop(std::shared_ptr<Shop> model);
    void removeShop(long long id);

    void clearAll();
    bool isEmpty() const;
};

#endif