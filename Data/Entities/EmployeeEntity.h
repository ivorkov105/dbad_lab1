#ifndef EMPLOYEE_ENTITY_H
#define EMPLOYEE_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class EmployeeEntity {
public:
    EmployeeEntity() : id(0), passport_id(0), shop_id(0), department_id(0) {
        birth_date.year = 0;
        birth_date.month = 0;
        birth_date.day = 0;
    }

    EmployeeEntity(long long id, const std::wstring& lastName, const std::wstring& firstName,
        const std::wstring& middleName, const std::wstring& address,
        SQL_DATE_STRUCT birthDate, long long passportId, long long shopId, long long departmentId)
        : id(id), last_name(lastName), first_name(firstName), middle_name(middleName),
        address(address), birth_date(birthDate), passport_id(passportId),
        shop_id(shopId), department_id(departmentId) {
    }

    long long getId() const { return id; }
    const std::wstring& getLastName() const { return last_name; }
    const std::wstring& getFirstName() const { return first_name; }
    const std::wstring& getMiddleName() const { return middle_name; }
    const std::wstring& getAddress() const { return address; }
    SQL_DATE_STRUCT getBirthDate() const { return birth_date; }
    long long getPassportId() const { return passport_id; }
    long long getShopId() const { return shop_id; }
    long long getDepartmentId() const { return department_id; }

    void setId(long long employeeId) { this->id = employeeId; }
    void setLastName(const std::wstring& lastName) { this->last_name = lastName; }
    void setFirstName(const std::wstring& firstName) { this->first_name = firstName; }
    void setMiddleName(const std::wstring& middleName) { this->middle_name = middleName; }
    void setAddress(const std::wstring& addr) { this->address = addr; }
    void setBirthDate(const SQL_DATE_STRUCT& birthDate) { this->birth_date = birthDate; }
    void setPassportId(long long passportId) { this->passport_id = passportId; }
    void setShopId(long long shopId) { this->shop_id = shopId; }
    void setDepartmentId(long long departmentId) { this->department_id = departmentId; }

private:
    long long id;
    std::wstring last_name;
    std::wstring first_name;
    std::wstring middle_name;
    std::wstring address;
    SQL_DATE_STRUCT birth_date;
    long long passport_id;
    long long shop_id;
    long long department_id;
};

#endif