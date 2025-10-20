#ifndef SALE_ENTITY_H
#define SALE_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class SaleEntity {
public:
    SaleEntity() : id(0), shop_id(0), product_id(0), employee_id(0), quantity_sold(0.0) {
        sale_date.year = 0;
        sale_date.month = 0;
        sale_date.day = 0;
        sale_date.hour = 0;
        sale_date.minute = 0;
        sale_date.second = 0;
        sale_date.fraction = 0;
    }

    SaleEntity(long long id, SQL_TIMESTAMP_STRUCT saleDate, long long shopId,
        long long productId, long long employeeId, double quantitySold)
        : id(id), sale_date(saleDate), shop_id(shopId), product_id(productId),
        employee_id(employeeId), quantity_sold(quantitySold) {
    }

    long long getId() const { return id; }
    SQL_TIMESTAMP_STRUCT getSaleDate() const { return sale_date; }
    long long getShopId() const { return shop_id; }
    long long getProductId() const { return product_id; }
    long long getEmployeeId() const { return employee_id; }
    double getQuantitySold() const { return quantity_sold; }

    void setId(long long saleId) { this->id = saleId; }
    void setSaleDate(const SQL_TIMESTAMP_STRUCT& date) { this->sale_date = date; }
    void setShopId(long long shopId) { this->shop_id = shopId; }
    void setProductId(long long productId) { this->product_id = productId; }
    void setEmployeeId(long long employeeId) { this->employee_id = employeeId; }
    void setQuantitySold(double quantity) { this->quantity_sold = quantity; }

private:
    long long id;
    SQL_TIMESTAMP_STRUCT sale_date;
    long long shop_id;
    long long product_id;
    long long employee_id;
    double quantity_sold;
};

#endif