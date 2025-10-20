#ifndef PASSPORT_ENTITY_H
#define PASSPORT_ENTITY_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class PassportEntity {
public:
    PassportEntity() : id(0) {
        issue_date.year = 0;
        issue_date.month = 0;
        issue_date.day = 0;
    }

    PassportEntity(long long id, const std::wstring& passportNumber,
        SQL_DATE_STRUCT issueDate, const std::wstring& issuingAuthority)
        : id(id), passport_number(passportNumber), issue_date(issueDate), issuing_authority(issuingAuthority) {
    }

    long long getId() const { return id; }
    const std::wstring& getPassportNumber() const { return passport_number; }
    SQL_DATE_STRUCT getIssueDate() const { return issue_date; }
    const std::wstring& getIssuingAuthority() const { return issuing_authority; }

    void setId(long long passportId) { this->id = passportId; }
    void setPassportNumber(const std::wstring& passportNum) { this->passport_number = passportNum; }
    void setIssueDate(const SQL_DATE_STRUCT& issueDate) { this->issue_date = issueDate; }
    void setIssuingAuthority(const std::wstring& authority) { this->issuing_authority = authority; }

private:
    long long id;
    std::wstring passport_number;
    SQL_DATE_STRUCT issue_date;
    std::wstring issuing_authority;
};

#endif