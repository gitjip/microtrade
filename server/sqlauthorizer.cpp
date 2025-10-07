#include "sqlauthorizer.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QSqlError>

SqlAuthorizer::SqlAuthorizer() {}

Authorization SqlAuthorizer::exec(const User &user) {
    QSqlQuery query(db);
    QDateTime current = QDateTime::currentDateTime();
    QByteArray bytes = (QString::number(user.id()) + current.toString()).toUtf8();
    QString token =
        QCryptographicHash::hash(bytes, QCryptographicHash::Sha256).toHex();
    query.prepare("INSERT INTO authorizations "
                  "(created_at,token,user_id) VALUES "
                  "(:created_at,:token,:user_id)");
    query.bindValue(":created_at", current);
    query.bindValue(":token", token);
    query.bindValue(":user_id", user.id());
    // qDebug() << "SqlAuthorizer::exec" << query.boundValueNames();
    // qDebug() << "SqlAuthorizer::exec" << query.boundValues();
    if (!query.exec()) {
        qDebug() << "SqlAuthorizer::exec" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    Authorization authorization{-1, {}, {}, -1, token};
    // qDebug() << "SqlAuthorizer::exec" << "success" << authorization.toJson();
    return authorization;
}
