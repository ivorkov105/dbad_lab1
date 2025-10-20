#ifndef PRODUCT_ENTITY_H
#define PRODUCT_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class ProductEntity {
public:
    ProductEntity() : id(0) {}

    ProductEntity(long long id, const std::wstring& name, const std::wstring& unit)
        : id(id), prod_name(name), unit(unit) {
    }

    long long getId() const { return id; }
    const std::wstring& getProdName() const { return prod_name; }
    const std::wstring& getUnit() const { return unit; }

    void setId(long long productId) { this->id = productId; }
    void setProdName(const std::wstring& name) { this->prod_name = name; }
    void setUnit(const std::wstring& u) { this->unit = u; }

private:
    long long id;
    std::wstring prod_name;
    std::wstring unit;
};

#endif