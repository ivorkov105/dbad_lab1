#ifndef SALE_H
#define SALE_H

#include <string>

class Sale {
public:
    long long getId() const { return id; }
    void setId(long long newId) { id = newId; }

    const std::wstring& getSaleDate() const { return saleDate; }
    void setSaleDate(const std::wstring& newDate) { saleDate = newDate; }

    long long getShopId() const { return shopId; }
    void setShopId(long long sId) { shopId = sId; }

    long long getProductId() const { return productId; }
    void setProductId(long long pId) { productId = pId; }

    long long getEmployeeId() const { return employeeId; }
    void setEmployeeId(long long eId) { employeeId = eId; }

    double getQuantitySold() const { return quantitySold; }
    void setQuantitySold(double newQuantity) { quantitySold = newQuantity; }

private:
    long long id;
    std::wstring saleDate;
    long long shopId;
    long long productId;
    long long employeeId;
    double quantitySold;
};

#endif