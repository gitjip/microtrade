#include "sqluseridfinder.h"
#include "configure.h"
#include <QSqlError>
#include <QSqlQuery>

SqlUserIdFinder::SqlUserIdFinder() {
    if(SqlServer::open(Configure::instance()->databaseName())){
        qDebug() << "SqlUserIdFinder::SqlUserIdFinder:"
                 << "successfully open database";
    }
}

QString SqlUserIdFinder::exec(const QString &username,
                              const QString &password) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username=:username AND "
                  "password=:password AND is_deleted=0");
    // if(!prepare){
    //     qDebug() << "SqlUserIdFinder::exec:" << "prepare failed";
    // }
    // if (!db.isOpen()) {
    //     qDebug() << "Database is not open!";
    //     return "";
    // }

    // qDebug() << "Database connection details:";
    // qDebug() << "  Driver:" << db.driverName();
    // qDebug() << "  Database name:" << db.databaseName();
    // qDebug() << "  Connection name:" << db.connectionName();
    // qDebug() << "  Is valid:" << db.isValid();

    query.bindValue(":username", username);
    query.bindValue(":password", password);
    // qDebug() << "Bound parameters:" << query.boundValueNames();
    // qDebug() << "Bound values:" << query.boundValues();
    if (!query.exec()) {
        qDebug() << "SqlUserIdFinder::exec: executing error -"
                 << query.lastError().text();
        return "";
    }
    if (!query.next()) {
        qDebug() << "SqlUserIdFinder::exec:" << "not found";
        return "";
    }
    QString userId = query.value("id").toString();
    qDebug() << "SqlUserIdFinder::exec:" << "user_id:" << userId;
    return userId;
}
