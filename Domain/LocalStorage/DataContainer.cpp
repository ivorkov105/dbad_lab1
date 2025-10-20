#include "DataContainer.h"
#include <algorithm>

DataContainer::DataContainer() {}

void DataContainer::addDepartment(std::shared_ptr<Department> model) {
    departments.push_back(model);
    departmentMap[model->getId()] = model;
}

std::shared_ptr<Department> DataContainer::findDepartmentById(long long id) {
    auto it = departmentMap.find(id);
    return (it != departmentMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Department>> DataContainer::getAllDepartments() {
    return departments;
}

void DataContainer::updateDepartment(std::shared_ptr<Department> model) {
    auto it = departmentMap.find(model->getId());
    if (it != departmentMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(departments.begin(), departments.end(),
            [id = model->getId()](const std::shared_ptr<Department>& d) {
                return d->getId() == id;
            });
        if (vecIt != departments.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removeDepartment(long long id) {
    if (departmentMap.erase(id) > 0) {
        departments.erase(std::remove_if(departments.begin(), departments.end(),
            [id](const std::shared_ptr<Department>& d) {
                return d->getId() == id;
            }), departments.end());
    }
}

void DataContainer::addEmployee(std::shared_ptr<Employee> model) {
    employees.push_back(model);
    employeeMap[model->getId()] = model;
}

std::shared_ptr<Employee> DataContainer::findEmployeeById(long long id) {
    auto it = employeeMap.find(id);
    return (it != employeeMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Employee>> DataContainer::getAllEmployees() {
    return employees;
}

void DataContainer::updateEmployee(std::shared_ptr<Employee> model) {
    auto it = employeeMap.find(model->getId());
    if (it != employeeMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(employees.begin(), employees.end(),
            [id = model->getId()](const std::shared_ptr<Employee>& e) {
                return e->getId() == id;
            });
        if (vecIt != employees.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removeEmployee(long long id) {
    if (employeeMap.erase(id) > 0) {
        employees.erase(std::remove_if(employees.begin(), employees.end(),
            [id](const std::shared_ptr<Employee>& e) {
                return e->getId() == id;
            }), employees.end());
    }
}

void DataContainer::addInventoryItem(std::shared_ptr<InventoryItem> model) {
    inventoryItems.push_back(model);
    invItemMap[{model->getShopId(), model->getProductId()}] = model;
}

std::shared_ptr<InventoryItem> DataContainer::findInventoryItemByIds(long long shopId, long long productId) {
    auto it = invItemMap.find({ shopId, productId });
    return (it != invItemMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<InventoryItem>> DataContainer::getAllInventoryItems() {
    return inventoryItems;
}

std::vector<std::shared_ptr<InventoryItem>> DataContainer::findAllInventoryItemsByShopId(long long shopId) {
    std::vector<std::shared_ptr<InventoryItem>> result;
    for (const auto& item : inventoryItems) {
        if (item->getShopId() == shopId) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<std::shared_ptr<InventoryItem>> DataContainer::findAllInventoryItemsByProductId(long long productId) {
    std::vector<std::shared_ptr<InventoryItem>> result;
    for (const auto& item : inventoryItems) {
        if (item->getProductId() == productId) {
            result.push_back(item);
        }
    }
    return result;
}

void DataContainer::updateInventoryItem(std::shared_ptr<InventoryItem> model) {
    auto key = std::make_pair(model->getShopId(), model->getProductId());
    auto it = invItemMap.find(key);
    if (it != invItemMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(inventoryItems.begin(), inventoryItems.end(),
            [&model](const std::shared_ptr<InventoryItem>& i) {
                return i->getShopId() == model->getShopId() && i->getProductId() == model->getProductId();
            });
        if (vecIt != inventoryItems.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removeInventoryItem(long long shopId, long long productId) {
    auto key = std::make_pair(shopId, productId);
    if (invItemMap.erase(key) > 0) {
        inventoryItems.erase(std::remove_if(inventoryItems.begin(), inventoryItems.end(),
            [shopId, productId](const std::shared_ptr<InventoryItem>& i) {
                return i->getShopId() == shopId && i->getProductId() == productId;
            }), inventoryItems.end());
    }
}

void DataContainer::addPassport(std::shared_ptr<Passport> model) {
    passports.push_back(model);
    passportMap[model->getId()] = model;
}

std::shared_ptr<Passport> DataContainer::findPassportById(long long id) {
    auto it = passportMap.find(id);
    return (it != passportMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Passport>> DataContainer::getAllPassports() {
    return passports;
}

void DataContainer::updatePassport(std::shared_ptr<Passport> model) {
    auto it = passportMap.find(model->getId());
    if (it != passportMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(passports.begin(), passports.end(),
            [id = model->getId()](const std::shared_ptr<Passport>& p) {
                return p->getId() == id;
            });
        if (vecIt != passports.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removePassport(long long id) {
    if (passportMap.erase(id) > 0) {
        passports.erase(std::remove_if(passports.begin(), passports.end(),
            [id](const std::shared_ptr<Passport>& p) {
                return p->getId() == id;
            }), passports.end());
    }
}

void DataContainer::addProduct(std::shared_ptr<Product> model) {
    products.push_back(model);
    productMap[model->getId()] = model;
}

std::shared_ptr<Product> DataContainer::findProductById(long long id) {
    auto it = productMap.find(id);
    return (it != productMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Product>> DataContainer::getAllProducts() {
    return products;
}

void DataContainer::updateProduct(std::shared_ptr<Product> model) {
    auto it = productMap.find(model->getId());
    if (it != productMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(products.begin(), products.end(),
            [id = model->getId()](const std::shared_ptr<Product>& p) {
                return p->getId() == id;
            });
        if (vecIt != products.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removeProduct(long long id) {
    if (productMap.erase(id) > 0) {
        products.erase(std::remove_if(products.begin(), products.end(),
            [id](const std::shared_ptr<Product>& p) {
                return p->getId() == id;
            }), products.end());
    }
}

void DataContainer::addSale(std::shared_ptr<Sale> model) {
    sales.push_back(model);
    saleMap[model->getId()] = model;
}

std::shared_ptr<Sale> DataContainer::findSaleById(long long id) {
    auto it = saleMap.find(id);
    return (it != saleMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Sale>> DataContainer::getAllSales() {
    return sales;
}

void DataContainer::updateSale(std::shared_ptr<Sale> model) {
    auto it = saleMap.find(model->getId());
    if (it != saleMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(sales.begin(), sales.end(),
            [id = model->getId()](const std::shared_ptr<Sale>& s) {
                return s->getId() == id;
            });
        if (vecIt != sales.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removeSale(long long id) {
    if (saleMap.erase(id) > 0) {
        sales.erase(std::remove_if(sales.begin(), sales.end(),
            [id](const std::shared_ptr<Sale>& s) {
                return s->getId() == id;
            }), sales.end());
    }
}

void DataContainer::addShop(std::shared_ptr<Shop> model) {
    shops.push_back(model);
    shopMap[model->getId()] = model;
}

std::shared_ptr<Shop> DataContainer::findShopById(long long id) {
    auto it = shopMap.find(id);
    return (it != shopMap.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Shop>> DataContainer::getAllShops() {
    return shops;
}

void DataContainer::updateShop(std::shared_ptr<Shop> model) {
    auto it = shopMap.find(model->getId());
    if (it != shopMap.end()) {
        it->second = model;
        auto vecIt = std::find_if(shops.begin(), shops.end(),
            [id = model->getId()](const std::shared_ptr<Shop>& s) {
                return s->getId() == id;
            });
        if (vecIt != shops.end()) {
            *vecIt = model;
        }
    }
}

void DataContainer::removeShop(long long id) {
    if (shopMap.erase(id) > 0) {
        shops.erase(std::remove_if(shops.begin(), shops.end(),
            [id](const std::shared_ptr<Shop>& s) {
                return s->getId() == id;
            }), shops.end());
    }
}

void DataContainer::clearAll() {
    departments.clear();
    employees.clear();
    inventoryItems.clear();
    passports.clear();
    products.clear();
    sales.clear();
    shops.clear();

    departmentMap.clear();
    employeeMap.clear();
    invItemMap.clear();
    passportMap.clear();
    productMap.clear();
    saleMap.clear();
    shopMap.clear();
}

bool DataContainer::isEmpty() const {
    return departments.empty() && employees.empty() &&
        inventoryItems.empty() && passports.empty() &&
        products.empty() && sales.empty() && shops.empty();
}