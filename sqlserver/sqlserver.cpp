#include "sqlserver.h"

SqlServer::SqlServer() {}

bool SqlServer::open(const QString &databaseName) {
    db.setDatabaseName(databaseName);
    db.addDatabase(databaseName);
    if(db.isOpen()) {
        qDebug() << "SqlServer::open: database not open";
        return false;
    }
    return true;
}
