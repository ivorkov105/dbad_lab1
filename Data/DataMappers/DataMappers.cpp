#include "DataMappers.h"
#include <string>
#include <cwchar>

Shop ShopMapper::toModel(const ShopEntity& entity) const {
    Shop model;
    model.setId(entity.getId());
    model.setName(entity.getName());
    model.setAddress(entity.getAddress());
    return model;
}

ShopEntity ShopMapper::toEntity(const Shop& model) const {
    ShopEntity entity;
    entity.setId(model.getId());
    entity.setName(model.getName());
    entity.setAddress(model.getAddress());
    return entity;
}

Department DepartmentMapper::toModel(const DepartmentEntity& entity) const {
    Department model;
    model.setId(entity.getId());
    model.setName(entity.getName());
    return model;
}

DepartmentEntity DepartmentMapper::toEntity(const Department& model) const {
    DepartmentEntity entity;
    entity.setId(model.getId());
    entity.setName(model.getName());
    return entity;
}

Passport PassportMapper::toModel(const PassportEntity& entity) const {
    Passport model;
    model.setId(entity.getId());
    model.setNum(entity.getPassportNumber());
    model.setAuthority(entity.getIssuingAuthority());

    SQL_DATE_STRUCT date = entity.getIssueDate();
    std::wstring dateStr = std::to_wstring(date.year) + L"-" +
        std::to_wstring(date.month) + L"-" +
        std::to_wstring(date.day);
    model.setIssueDate(dateStr);
    return model;
}

PassportEntity PassportMapper::toEntity(const Passport& model) const {
    PassportEntity entity;
    entity.setId(model.getId());
    entity.setPassportNumber(model.getNum());
    entity.setIssuingAuthority(model.getAuthority());

    SQL_DATE_STRUCT date{};
    swscanf_s(model.getIssueDate().c_str(), L"%hd-%hd-%hd", &date.year, &date.month, &date.day);
    entity.setIssueDate(date);
    return entity;
}

Product ProductMapper::toModel(const ProductEntity& entity) const {
    Product model;
    model.setId(entity.getId());
    model.setName(entity.getProdName());
    model.setUnit(entity.getUnit());
    return model;
}

ProductEntity ProductMapper::toEntity(const Product& model) const {
    ProductEntity entity;
    entity.setId(model.getId());
    entity.setProdName(model.getName());
    entity.setUnit(model.getUnit());
    return entity;
}

Employee EmployeeMapper::toModel(const EmployeeEntity& entity) const {
    Employee model;
    model.setId(entity.getId());
    model.setLastName(entity.getLastName());
    model.setFirstName(entity.getFirstName());
    model.setMiddleName(entity.getMiddleName());
    model.setAddress(entity.getAddress());

    SQL_DATE_STRUCT date = entity.getBirthDate();
    std::wstring dateStr = std::to_wstring(date.year) + L"-" +
        std::to_wstring(date.month) + L"-" +
        std::to_wstring(date.day);
    model.setBirthDate(dateStr);

    model.setPassportId(entity.getPassportId());
    model.setShopId(entity.getShopId());
    model.setDepartmentId(entity.getDepartmentId());
    return model;
}

EmployeeEntity EmployeeMapper::toEntity(const Employee& model) const {
    EmployeeEntity entity;
    entity.setId(model.getId());
    entity.setLastName(model.getLastName());
    entity.setFirstName(model.getFirstName());
    entity.setMiddleName(model.getMiddleName());
    entity.setAddress(model.getAddress());

    SQL_DATE_STRUCT date{};
    swscanf_s(model.getBirthDate().c_str(), L"%hd-%hd-%hd", &date.year, &date.month, &date.day);
    entity.setBirthDate(date);

    entity.setPassportId(model.getPassportId());
    entity.setShopId(model.getShopId());
    entity.setDepartmentId(model.getDepartmentId());
    return entity;
}

InventoryItem InventoryItemMapper::toModel(const InventoryItemEntity& entity) const {
    InventoryItem model;
    model.setShopId(entity.getShopId());
    model.setProductId(entity.getProductId());
    model.setQuantity(entity.getQuantity());
    model.setPrice(entity.getPrice());
    return model;
}

InventoryItemEntity InventoryItemMapper::toEntity(const InventoryItem& model) const {
    InventoryItemEntity entity;
    entity.setShopId(model.getShopId());
    entity.setProductId(model.getProductId());
    entity.setQuantity(model.getQuantity());
    entity.setPrice(model.getPrice());
    return entity;
}

Sale SaleMapper::toModel(const SaleEntity& entity) const {
    Sale model;
    model.setId(entity.getId());

    SQL_TIMESTAMP_STRUCT ts = entity.getSaleDate();
    std::wstring tsStr = std::to_wstring(ts.year) + L"-" + std::to_wstring(ts.month) + L"-" + std::to_wstring(ts.day) +
        L" " + std::to_wstring(ts.hour) + L":" + std::to_wstring(ts.minute) + L":" + std::to_wstring(ts.second);
    model.setSaleDate(tsStr);

    model.setShopId(entity.getShopId());
    model.setProductId(entity.getProductId());
    model.setEmployeeId(entity.getEmployeeId());
    model.setQuantitySold(entity.getQuantitySold());
    return model;
}

SaleEntity SaleMapper::toEntity(const Sale& model) const {
    SaleEntity entity;
    entity.setId(model.getId());

    SQL_TIMESTAMP_STRUCT ts{};
    swscanf_s(model.getSaleDate().c_str(), L"%hd-%hd-%hd %hd:%hd:%hd",
        &ts.year, &ts.month, &ts.day,
        &ts.hour, &ts.minute, &ts.second);
    ts.fraction = 0;
    entity.setSaleDate(ts);

    entity.setShopId(model.getShopId());
    entity.setProductId(model.getProductId());
    entity.setEmployeeId(model.getEmployeeId());
    entity.setQuantitySold(model.getQuantitySold());
    return entity;
}