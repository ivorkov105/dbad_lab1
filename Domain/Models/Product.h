#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    long long getId() const { return id; }
    void setId(long long newId) { id = newId; }

    const std::wstring& getName() const { return name; }
    void setName(const std::wstring& newName) { name = newName; }

    const std::wstring& getUnit() const { return unit; }
    void setUnit(const std::wstring& newUnit) { unit = newUnit; }

private:
    long long id;
    std::wstring name;
    std::wstring unit;
};

#endif