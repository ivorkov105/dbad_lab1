#ifndef SHOP_H
#define SHOP_H

#include <string>

class Shop {
public:
    long long getId() const { return id; }
    void setId(long long newId) { id = newId; }

    const std::wstring& getName() const { return name; }
    void setName(const std::wstring& newName) { name = newName; }

    const std::wstring& getAddress() const { return address; }
    void setAddress(const std::wstring& newAddress) { address = newAddress; }

private:
    long long id;
    std::wstring name;
    std::wstring address;
};

#endif