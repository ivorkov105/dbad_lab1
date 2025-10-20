#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <windows.h> 
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>

class DatabaseConnection {
public:
	virtual ~DatabaseConnection() = default;
	virtual SQLHDBC getHDBC() const = 0;
	virtual bool connect() = 0;
	virtual bool disconnect() = 0;
};

#endif