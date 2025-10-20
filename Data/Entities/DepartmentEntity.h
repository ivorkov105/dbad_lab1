#ifndef DEPARTMENT_ENTITY_H
#define DEPARTMENT_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class DepartmentEntity {
public:
    DepartmentEntity() : id(0), name(L"") {}

    DepartmentEntity(long long id, const std::wstring& name)
        : id(id), name(name) {
    }

    long long getId() const {
        return id;
    }

    const std::wstring& getName() const {
        return name;
    }

    void setId(long long departmentId) {
        this->id = departmentId;
    }

    void setName(const std::wstring& departmentName) {
        this->name = departmentName;
    }

private:
    long long id;
    std::wstring name;
};

#endif