#include "sqlquery.h"

namespace My {
SqlQuery::SqlQuery() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName("my.db");
}

SqlQuery::~SqlQuery() {}
} // namespace My
