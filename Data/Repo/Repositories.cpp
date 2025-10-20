#include "Repositories.h"
#include <iostream>
#include <set>

ShopRepository::ShopRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<ShopMapper> mapper, std::shared_ptr<ShopDAO> dao, std::shared_ptr<InventoryItemDAO> invDao)
    : dataContainer(container), mapper(mapper), dao(dao), invDao(invDao) {
}

std::shared_ptr<Shop> ShopRepository::find(const Shop& model) {
    long long id = model.getId();
    auto cachedModel = dataContainer->findShopById(id);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(id);
        if (entity) {
            auto newModel = std::make_shared<Shop>(mapper->toModel(*entity));
            dataContainer->addShop(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<Shop>> ShopRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllShops();
        for (const auto& oldModel : current_models) {
            dataContainer->removeShop(oldModel->getId());
        }
        for (const auto& entity : entities) {
            dataContainer->addShop(std::make_shared<Shop>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllShops();
}

std::vector<std::shared_ptr<Shop>> ShopRepository::findAllByProduct(const Product& model) {
    long long productId = model.getId();
    std::set<long long> shopIds;
    try {
        auto entities = invDao->findAllByProductId(productId);
        for(const auto& entity : entities) {
            shopIds.insert(entity->getShopId());
        }
    }
    catch (const std::exception& e) {
        auto items = dataContainer->findAllInventoryItemsByProductId(productId);
        for(const auto& item : items) {
            shopIds.insert(item->getShopId());
        }
    }
    
    std::vector<std::shared_ptr<Shop>> shops;
    for (long long id : shopIds) {
        Shop tempShop;
        tempShop.setId(id);
        if(auto shop = find(tempShop)) {
            shops.push_back(shop);
        }
    }
    return shops;
}

void ShopRepository::add(const Shop& model) {
    dataContainer->addShop(std::make_shared<Shop>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void ShopRepository::update(const Shop& model) {
    dataContainer->updateShop(std::make_shared<Shop>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void ShopRepository::remove(const Shop& model) {
    long long id = model.getId();
    dataContainer->removeShop(id);
    try {
        dao->remove(id);
    }
    catch (const std::exception& e) {}
}

DepartmentRepository::DepartmentRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<DepartmentMapper> mapper, std::shared_ptr<DepartmentDAO> dao)
    : dataContainer(container), mapper(mapper), dao(dao) {
}

std::shared_ptr<Department> DepartmentRepository::find(const Department& model) {
    long long id = model.getId();
    auto cachedModel = dataContainer->findDepartmentById(id);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(id);
        if (entity) {
            auto newModel = std::make_shared<Department>(mapper->toModel(*entity));
            dataContainer->addDepartment(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<Department>> DepartmentRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllDepartments();
        for (const auto& oldModel : current_models) {
            dataContainer->removeDepartment(oldModel->getId());
        }
        for (const auto& entity : entities) {
            dataContainer->addDepartment(std::make_shared<Department>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllDepartments();
}

void DepartmentRepository::add(const Department& model) {
    dataContainer->addDepartment(std::make_shared<Department>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void DepartmentRepository::update(const Department& model) {
    dataContainer->updateDepartment(std::make_shared<Department>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void DepartmentRepository::remove(const Department& model) {
    long long id = model.getId();
    dataContainer->removeDepartment(id);
    try {
        dao->remove(id);
    }
    catch (const std::exception& e) {}
}

PassportRepository::PassportRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<PassportMapper> mapper, std::shared_ptr<PassportDAO> dao)
    : dataContainer(container), mapper(mapper), dao(dao) {
}

std::shared_ptr<Passport> PassportRepository::find(const Passport& model) {
    long long id = model.getId();
    auto cachedModel = dataContainer->findPassportById(id);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(id);
        if (entity) {
            auto newModel = std::make_shared<Passport>(mapper->toModel(*entity));
            dataContainer->addPassport(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<Passport>> PassportRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllPassports();
        for (const auto& oldModel : current_models) {
            dataContainer->removePassport(oldModel->getId());
        }
        for (const auto& entity : entities) {
            dataContainer->addPassport(std::make_shared<Passport>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllPassports();
}

void PassportRepository::add(const Passport& model) {
    dataContainer->addPassport(std::make_shared<Passport>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void PassportRepository::update(const Passport& model) {
    dataContainer->updatePassport(std::make_shared<Passport>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void PassportRepository::remove(const Passport& model) {
    long long id = model.getId();
    dataContainer->removePassport(id);
    try {
        dao->remove(id);
    }
    catch (const std::exception& e) {}
}

ProductRepository::ProductRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<ProductMapper> mapper, std::shared_ptr<ProductDAO> dao, std::shared_ptr<InventoryItemDAO> invDao)
    : dataContainer(container), mapper(mapper), dao(dao), invDao(invDao) {
}

std::shared_ptr<Product> ProductRepository::find(const Product& model) {
    long long id = model.getId();
    auto cachedModel = dataContainer->findProductById(id);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(id);
        if (entity) {
            auto newModel = std::make_shared<Product>(mapper->toModel(*entity));
            dataContainer->addProduct(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<Product>> ProductRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllProducts();
        for (const auto& oldModel : current_models) {
            dataContainer->removeProduct(oldModel->getId());
        }
        for (const auto& entity : entities) {
            dataContainer->addProduct(std::make_shared<Product>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllProducts();
}

std::vector<std::shared_ptr<Product>> ProductRepository::findAllByShop(const Shop& model) {
    long long shopId = model.getId();
    std::set<long long> productIds;
    try {
        auto entities = invDao->findAllByShopId(shopId);
        for (const auto& entity : entities) {
            productIds.insert(entity->getProductId());
        }
    }
    catch (const std::exception& e) {
        auto items = dataContainer->findAllInventoryItemsByShopId(shopId);
        for (const auto& item : items) {
            productIds.insert(item->getProductId());
        }
    }
    
    std::vector<std::shared_ptr<Product>> products;
    for (long long id : productIds) {
        Product tempProduct;
        tempProduct.setId(id);
        if (auto product = find(tempProduct)) {
            products.push_back(product);
        }
    }
    return products;
}

void ProductRepository::add(const Product& model) {
    dataContainer->addProduct(std::make_shared<Product>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void ProductRepository::update(const Product& model) {
    dataContainer->updateProduct(std::make_shared<Product>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void ProductRepository::remove(const Product& model) {
    long long id = model.getId();
    dataContainer->removeProduct(id);
    try {
        dao->remove(id);
    }
    catch (const std::exception& e) {}
}

EmployeeRepository::EmployeeRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<EmployeeMapper> mapper, std::shared_ptr<EmployeeDAO> dao)
    : dataContainer(container), mapper(mapper), dao(dao) {
}

std::shared_ptr<Employee> EmployeeRepository::find(const Employee& model) {
    long long id = model.getId();
    auto cachedModel = dataContainer->findEmployeeById(id);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(id);
        if (entity) {
            auto newModel = std::make_shared<Employee>(mapper->toModel(*entity));
            dataContainer->addEmployee(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<Employee>> EmployeeRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllEmployees();
        for (const auto& oldModel : current_models) {
            dataContainer->removeEmployee(oldModel->getId());
        }
        for (const auto& entity : entities) {
            dataContainer->addEmployee(std::make_shared<Employee>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllEmployees();
}

void EmployeeRepository::add(const Employee& model) {
    dataContainer->addEmployee(std::make_shared<Employee>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void EmployeeRepository::update(const Employee& model) {
    dataContainer->updateEmployee(std::make_shared<Employee>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void EmployeeRepository::remove(const Employee& model) {
    long long id = model.getId();
    dataContainer->removeEmployee(id);
    try {
        dao->remove(id);
    }
    catch (const std::exception& e) {}
}

InventoryItemRepository::InventoryItemRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<InventoryItemMapper> mapper, std::shared_ptr<InventoryItemDAO> dao)
    : dataContainer(container), mapper(mapper), dao(dao) {
}

std::shared_ptr<InventoryItem> InventoryItemRepository::find(const InventoryItem& model) {
    long long shopId = model.getShopId();
    long long productId = model.getProductId();
    auto cachedModel = dataContainer->findInventoryItemByIds(shopId, productId);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(shopId, productId);
        if (entity) {
            auto newModel = std::make_shared<InventoryItem>(mapper->toModel(*entity));
            dataContainer->addInventoryItem(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<InventoryItem>> InventoryItemRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllInventoryItems();
        for (const auto& oldModel : current_models) {
            dataContainer->removeInventoryItem(oldModel->getShopId(), oldModel->getProductId());
        }
        for (const auto& entity : entities) {
            dataContainer->addInventoryItem(std::make_shared<InventoryItem>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllInventoryItems();
}

std::vector<std::shared_ptr<InventoryItem>> InventoryItemRepository::findAllByShop(const Shop& model) {
    long long shopId = model.getId();
    std::vector<std::shared_ptr<InventoryItem>> models;
    try {
        auto entities = dao->findAllByShopId(shopId);
        auto cachedItems = dataContainer->findAllInventoryItemsByShopId(shopId);
        
        for (const auto& oldModel : cachedItems) {
            dataContainer->removeInventoryItem(oldModel->getShopId(), oldModel->getProductId());
        }
        
        for (const auto& entity : entities) {
            auto newModel = std::make_shared<InventoryItem>(mapper->toModel(*entity));
            dataContainer->addInventoryItem(newModel);
            models.push_back(newModel);
        }
    }
    catch (const std::exception& e) {
        return dataContainer->findAllInventoryItemsByShopId(shopId);
    }
    return models;
}

void InventoryItemRepository::add(const InventoryItem& model) {
    dataContainer->addInventoryItem(std::make_shared<InventoryItem>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void InventoryItemRepository::update(const InventoryItem& model) {
    dataContainer->updateInventoryItem(std::make_shared<InventoryItem>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void InventoryItemRepository::remove(const InventoryItem& model) {
    long long shopId = model.getShopId();
    long long productId = model.getProductId();
    dataContainer->removeInventoryItem(shopId, productId);
    try {
        dao->remove(shopId, productId);
    }
    catch (const std::exception& e) {}
}

SaleRepository::SaleRepository(std::shared_ptr<DataContainer> container, std::shared_ptr<SaleMapper> mapper, std::shared_ptr<SaleDAO> dao)
    : dataContainer(container), mapper(mapper), dao(dao) {
}

std::shared_ptr<Sale> SaleRepository::find(const Sale& model) {
    long long id = model.getId();
    auto cachedModel = dataContainer->findSaleById(id);
    if (cachedModel) {
        return cachedModel;
    }
    try {
        auto entity = dao->findById(id);
        if (entity) {
            auto newModel = std::make_shared<Sale>(mapper->toModel(*entity));
            dataContainer->addSale(newModel);
            return newModel;
        }
    }
    catch (const std::exception& e) {}
    return nullptr;
}

std::vector<std::shared_ptr<Sale>> SaleRepository::findAll() {
    try {
        auto entities = dao->findAll();
        auto current_models = dataContainer->getAllSales();
        for (const auto& oldModel : current_models) {
            dataContainer->removeSale(oldModel->getId());
        }
        for (const auto& entity : entities) {
            dataContainer->addSale(std::make_shared<Sale>(mapper->toModel(*entity)));
        }
    }
    catch (const std::exception& e) {}
    return dataContainer->getAllSales();
}

void SaleRepository::add(const Sale& model) {
    dataContainer->addSale(std::make_shared<Sale>(model));
    try {
        dao->add(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void SaleRepository::update(const Sale& model) {
    dataContainer->updateSale(std::make_shared<Sale>(model));
    try {
        dao->update(mapper->toEntity(model));
    }
    catch (const std::exception& e) {}
}

void SaleRepository::remove(const Sale& model) {
    long long id = model.getId();
    dataContainer->removeSale(id);
    try {
        dao->remove(id);
    }
    catch (const std::exception& e) {}
}