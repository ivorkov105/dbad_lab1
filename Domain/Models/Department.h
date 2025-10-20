#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
class Department {
public:
	long long getId() const { return id; }
	void setId(long long newId) { id = newId; }
	const std::wstring& getName() const { return name; }
	void setName(const std::wstring& newName) { name = newName; }
private:
	long long id;
	std::wstring name;
};
#endif