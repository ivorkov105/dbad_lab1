#ifndef PASSPORT_H
#define PASSPORT_H

#include <string>

class Passport {
public:
    long long getId() const { return id; }
    void setId(long long newId) { id = newId; }

    const std::wstring& getNum() const { return passportNumber; }
    void setNum(const std::wstring& newNumber) { passportNumber = newNumber; }

    const std::wstring& getIssueDate() const { return issueDate; }
    void setIssueDate(const std::wstring& newDate) { issueDate = newDate; }

    const std::wstring& getAuthority() const { return issuingAuthority; }
    void setAuthority(const std::wstring& newAuthority) { issuingAuthority = newAuthority; }

private:
    long long id;
    std::wstring passportNumber;
    std::wstring issueDate;
    std::wstring issuingAuthority;
};

#endif