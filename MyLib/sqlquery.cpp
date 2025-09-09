#include "sqlquery.h"
#include "constants.h"

namespace My {
SqlQuery::SqlQuery() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(My::rootAppName + ".db");
}

SqlQuery::~SqlQuery() {}
} // namespace My
