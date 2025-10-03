#include "sqlpayer.h"
#include "config.h"
#include <QSqlError>

SqlPayer::SqlPayer() {
    if (SqlServer::open(Config::instance()->databaseName())) {
        qDebug() << "SqlPayer::SqlPayer:"
                 << "successfully open database";
    }
}

bool SqlPayer::exec(const QString &productId){
    qDebug() << "SqlPayer::exec:" << "productId:" << productId;
    QSqlQuery query(db);

    return false;
}
