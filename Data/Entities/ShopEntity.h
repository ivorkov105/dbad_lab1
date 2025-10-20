#ifndef SHOP_ENTITY_H
#define SHOP_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class ShopEntity {
public:
    ShopEntity() : id(0) {}

    ShopEntity(long long id, const std::wstring& name, const std::wstring& address)
        : id(id), name(name), address(address) {
    }

    long long getId() const { return id; }
    const std::wstring& getName() const { return name; }
    const std::wstring& getAddress() const { return address; }

    void setId(long long shopId) { this->id = shopId; }
    void setName(const std::wstring& shopName) { this->name = shopName; }
    void setAddress(const std::wstring& shopAddress) { this->address = shopAddress; }

private:
    long long id;
    std::wstring name;
    std::wstring address;
};

#endif