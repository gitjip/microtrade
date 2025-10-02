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
    query.prepare("UPDATE products SET stock = stock - 1 WHERE id=:id");
    return false;
}
