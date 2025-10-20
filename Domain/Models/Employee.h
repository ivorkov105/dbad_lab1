#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
public:
    long long getId() const { return id; }
    void setId(long long newId) { id = newId; }

    const std::wstring& getLastName() const { return lastName; }
    void setLastName(const std::wstring& name) { lastName = name; }

    const std::wstring& getFirstName() const { return firstName; }
    void setFirstName(const std::wstring& name) { firstName = name; }

    const std::wstring& getMiddleName() const { return middleName; }
    void setMiddleName(const std::wstring& name) { middleName = name; }

    std::wstring getFullName() const { return lastName + L" " + firstName + L" " + middleName; }

    const std::wstring& getAddress() const { return address; }
    void setAddress(const std::wstring& addr) { address = addr; }

    const std::wstring& getBirthDate() const { return birthDate; }
    void setBirthDate(const std::wstring& date) { birthDate = date; }

    long long getPassportId() const { return passportId; }
    void setPassportId(long long pId) { passportId = pId; }

    long long getShopId() const { return shopId; }
    void setShopId(long long sId) { shopId = sId; }

    long long getDepartmentId() const { return departmentId; }
    void setDepartmentId(long long dId) { departmentId = dId; }

private:
    long long id;
    std::wstring lastName, firstName, middleName;
    std::wstring address;
    std::wstring birthDate;
    long long passportId;
    long long shopId;
    long long departmentId;
};

#endif