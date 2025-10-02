#include "sqltokengenerator.h"
#include "config.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QSqlError>

SqlTokenGenerator::SqlTokenGenerator() {
    SqlServer::open(Config::instance()->databaseName());
}

QString SqlTokenGenerator::exec(const QString &userId) {
    QSqlQuery query(db);
    QDateTime current = QDateTime::currentDateTime();
    QString token = QCryptographicHash::hash(
        (userId + current.toString()).toUtf8(), QCryptographicHash::Sha256).toHex();
    query.prepare("INSERT INTO login_records "
                  "(authorized_token,user_id,loggedin_at,is_deleted) VALUES "
                  "(:authorized_token,:user_id,:loggedin_at,0)");
    query.bindValue(":authorized_token", token);
    query.bindValue(":user_id", userId);
    query.bindValue(":loggedin_at", current);
    if (!query.exec()) {
        qDebug() << "SqlTokenGenerator::exec:" << "executing error -"
                 << query.lastError().text();
        return "";
    }
    qDebug() << "SqlTokenGenerator::exec:" << "token:" << token;
    return token;
}
