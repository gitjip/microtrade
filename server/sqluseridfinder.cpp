#include "sqluseridfinder.h"
#include "config.h"
#include <QSqlError>
#include <QSqlQuery>

SqlUserIdFinder::SqlUserIdFinder() {
    if (SqlServer::open(Config::instance()->databaseName())) {
        qDebug() << "SqlUserIdFinder::SqlUserIdFinder:"
                 << "successfully open database";
    }
}

QString SqlUserIdFinder::exec(const QString &username,
                              const QString &password) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username=:username AND "
                  "password=:password AND is_deleted=0");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (!query.exec()) {
        qDebug() << "SqlUserIdFinder::exec:" << "executing error:"
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
