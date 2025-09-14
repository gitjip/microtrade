#include "usercontroller.h"
#include <QSqlQuery>

namespace My {
UserController::UserController(QObject *parent) : Controller{parent} {
    QSqlQuery query(db);
    qDebug() << db.databaseName();
    if (!query.exec("CREATE TABLE IF NOT EXISTS users(id INT PRIMARY KEY, "
                    "username TEXT NOT NULL, password TEXT NOT NULL);")) {
        qDebug() << "failed to create table users";
    }
}

Response UserController::get(const QJsonObject &headers,
                             const QJsonValue &body) {
    Q_UNUSED(body);
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM users WHERE username=:username AND password=:password;");
    query.bindValue(":username", headers["username"].toString());
    query.bindValue(":password", headers["password"].toString());
    if (!query.exec()) {
        return Response(1, QJsonObject(), QJsonValue(), "runtime error");
    }
    if (!query.next()) {
        return Response(1, QJsonObject(), QJsonValue(), "user not found");
    }
    QJsonObject responseBody;
    responseBody["id"] = query.value(0).toInt();
    return Response(200, QJsonObject(), responseBody, "");
}

Response UserController::post(const QJsonObject &headers,
                              const QJsonValue &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM users WHERE username=:username AND password=:password");
    query.bindValue(":username", body["username"].toString());
    query.bindValue(":password", body["password"].toString());
    if (!query.exec()) {
        return Response(1, QJsonObject(), QJsonValue(), "runtime error");
    }
    if (query.next()) {
        return Response(1, QJsonObject(), QJsonValue(), "user already exists");
    }
    query.prepare("INSERT (username, password) INTO users VALUES(:username, "
                  ":password)");
    query.bindValue(":username", body["username"].toString());
    query.bindValue(":password", body["password"].toString());
    if (!query.exec()) {
        return Response(1, QJsonObject(), QJsonValue(), "runtime error");
    }
    QJsonObject responseBody;
    responseBody["id"] = query.value(0).toInt();
    return Response(200, QJsonObject(), responseBody, "");
}

Response UserController::put(const QJsonObject &headers,
                             const QJsonValue &body) {
    Q_UNUSED(headers);
    Q_UNUSED(body);
    return Response(0, QJsonObject(), QJsonValue(), "undefined");
}

Response UserController::del(const QJsonObject &headers,
                             const QJsonValue &body) {
    Q_UNUSED(headers);
    Q_UNUSED(body);
    return Response(0, QJsonObject(), QJsonValue(), "undefined");
}
} // namespace My
