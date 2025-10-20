#ifndef DATA_MAPPERS_H
#define DATA_MAPPERS_H

#include <vector>
#include <memory>
#include "../../Domain/Models/Shop.h"
#include "../../Domain/Models/Department.h"
#include "../../Domain/Models/Passport.h"
#include "../../Domain/Models/Product.h"
#include "../../Domain/Models/Employee.h"
#include "../../Domain/Models/InventoryItem.h"
#include "../../Domain/Models/Sale.h"
#include "../Entities/ShopEntity.h"
#include "../Entities/DepartmentEntity.h"
#include "../Entities/PassportEntity.h"
#include "../Entities/ProductEntity.h"
#include "../Entities/EmployeeEntity.h"
#include "../Entities/InventoryItemEntity.h"
#include "../Entities/SaleEntity.h"

class ShopMapper {
public:
    ShopMapper() = default;
    Shop toModel(const ShopEntity& entity) const;
    ShopEntity toEntity(const Shop& model) const;
};

class DepartmentMapper {
public:
    DepartmentMapper() = default;
    Department toModel(const DepartmentEntity& entity) const;
    DepartmentEntity toEntity(const Department& model) const;
};

class PassportMapper {
public:
    PassportMapper() = default;
    Passport toModel(const PassportEntity& entity) const;
    PassportEntity toEntity(const Passport& model) const;
};

class ProductMapper {
public:
    ProductMapper() = default;
    Product toModel(const ProductEntity& entity) const;
    ProductEntity toEntity(const Product& model) const;
};

class EmployeeMapper {
public:
    EmployeeMapper() = default;
    Employee toModel(const EmployeeEntity& entity) const;
    EmployeeEntity toEntity(const Employee& model) const;
};

class InventoryItemMapper {
public:
    InventoryItemMapper() = default;
    InventoryItem toModel(const InventoryItemEntity& entity) const;
    InventoryItemEntity toEntity(const InventoryItem& model) const;
};

class SaleMapper {
public:
    SaleMapper() = default;
    Sale toModel(const SaleEntity& entity) const;
    SaleEntity toEntity(const Sale& model) const;
};

#endif