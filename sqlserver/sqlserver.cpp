#include "sqlserver.h"

SqlServer::SqlServer() {}

bool SqlServer::open(const QString &databaseName) {
    if (db.contains(QSqlDatabase::defaultConnection)) {
        db = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", QSqlDatabase::defaultConnection);
    }
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qDebug() << "SqlServer::open:" << "database not open";
        return false;
    }
    qDebug() << "SqlServer::open:" << "successfully open" << db.databaseName();
    return true;
}
