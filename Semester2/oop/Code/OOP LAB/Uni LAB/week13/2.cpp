#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

int main() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;

    SQLRETURN status;

    status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (status != SQL_SUCCESS) cout << "NOT DB CONNECTED."; return 0;

    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    SQLCHAR connectionString[] =
        "DRIVER={ODBC Driver 17 for SQL Server};"
        "SERVER=localhost;"
        "DATABASE=TestDB;"
        "Trusted_Connection=Yes;";

    status = SQLDriverConnectA(
        dbc,
        NULL,
        connectionString,
        SQL_NTS,
        NULL,
        0,
        NULL,
        SQL_DRIVER_COMPLETE
    );

    if (status != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO) {
        cout << "Database connection failed\n";
        return 0;
    }

    cout << "Database connected successfully\n";

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLExecDirectA(
        stmt,
        (SQLCHAR*)
        "IF OBJECT_ID('StudentsODBC', 'U') IS NULL "
        "CREATE TABLE StudentsODBC ("
        "id INT IDENTITY(1,1) PRIMARY KEY, "
        "name VARCHAR(50), "
        "marks INT)",
        SQL_NTS
    );

    SQLExecDirectA(
        stmt,
        (SQLCHAR*)"INSERT INTO StudentsODBC VALUES ('Ali', 85)",
        SQL_NTS
    );

    SQLExecDirectA(
        stmt,
        (SQLCHAR*)"INSERT INTO StudentsODBC VALUES ('Ahmed', 90)",
        SQL_NTS
    );

    SQLExecDirectA(
        stmt,
        (SQLCHAR*)"SELECT * FROM StudentsODBC",
        SQL_NTS
    );

    int id, marks;
    char name[50];

    cout << "\nID   NAME     MARKS\n";
    cout << "-------------------\n";

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
        SQLGetData(stmt, 3, SQL_C_LONG, &marks, 0, NULL);

        cout << id << "   " << name << "   " << marks << endl;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return 0;
}
