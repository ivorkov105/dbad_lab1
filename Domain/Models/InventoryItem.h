#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

class InventoryItem {
public:
    long long getShopId() const { return shopId; }
    void setShopId(long long sId) { shopId = sId; }

    long long getProductId() const { return productId; }
    void setProductId(long long pId) { productId = pId; }

    double getQuantity() const { return quantity; }
    void setQuantity(double newQuantity) { quantity = newQuantity; }

    double getPrice() const { return price; }
    void setPrice(double newPrice) { price = newPrice; }

private:
    long long shopId;
    long long productId;
    double quantity;
    double price;
};

#endif