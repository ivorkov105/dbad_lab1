#ifndef INVENTORY_ITEM_ENTITY_H
#define INVENTORY_ITEM_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class InventoryItemEntity {
public:
    InventoryItemEntity() : shop_id(0), product_id(0), quantity(0.0), price(0.0) {}

    InventoryItemEntity(long long shopId, long long productId, double quantity, double price)
        : shop_id(shopId), product_id(productId), quantity(quantity), price(price) {
    }

    long long getShopId() const { return shop_id; }
    long long getProductId() const { return product_id; }
    double getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setShopId(long long shopId) { this->shop_id = shopId; }
    void setProductId(long long productId) { this->product_id = productId; }
    void setQuantity(double quant) { this->quantity = quant; }
    void setPrice(double p) { this->price = p; }

private:
    long long shop_id;
    long long product_id;
    double quantity;
    double price;
};

#endif