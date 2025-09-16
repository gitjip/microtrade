#include "usercontroller.h"
#include <QSqlError>
#include <QSqlQuery>

namespace My {
UserController::UserController(QObject *parent) : Controller{parent} {
    QSqlQuery query(db);
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE NOT "
            "NULL, password TEXT NOT NULL);")) {
        qDebug() << "创建用户数据库失败";
    }
}

Response UserController::get(const QJsonObject &headers,
                             const QJsonValue &body) {
    Q_UNUSED(body);
    QSqlQuery query(db);
    if (headers["username"].toString().isEmpty() ||
        headers["password"].toString().isEmpty()) {
        return Response(400, QJsonObject(), QJsonValue(), "用户名和密码不能为空");
    }
    query.prepare(
        "SELECT rowid, * FROM users WHERE username = :username AND password = "
        ":password;");
    query.bindValue(":username", headers["username"].toString());
    query.bindValue(":password", headers["password"].toString());
    if (!query.exec()) {
        return Response(500, QJsonObject(), QJsonValue(), "查询用户时错误");
    }
    if (!query.next()) {
        return Response(404, QJsonObject(), QJsonValue(), "用户未找到");
    }
    QJsonObject responseBody;
    responseBody["id"] = query.value("rowid").toInt();
    responseBody["username"] = query.value("username").toString();
    responseBody["password"] = query.value("password").toString();
    return Response(200, QJsonObject(), responseBody, "");
}

Response UserController::post(const QJsonObject &headers,
                              const QJsonValue &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    if (body["username"].toString().isEmpty() ||
        body["password"].toString().isEmpty()) {
        return Response(400, QJsonObject(), QJsonValue(), "用户名和密码不能为空");
    }
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", body["username"].toString());
    if (!query.exec()) {
        return Response(500, QJsonObject(), QJsonValue(), "查询用户时错误");
    }
    if (query.next()) {
        return Response(403, QJsonObject(), QJsonValue(), "用户已存在");
    }
    query.prepare("INSERT INTO users (username, password) VALUES (:username, "
                  ":password)");
    query.bindValue(":username", body["username"].toString());
    query.bindValue(":password", body["password"].toString());
    if (!query.exec()) {
        return Response(500, QJsonObject(), QJsonValue(), "添加用户时错误");
    }
    return Response(200, QJsonObject(), QJsonObject(), "成功");
}

Response UserController::put(const QJsonObject &headers,
                             const QJsonValue &body) {
    Q_UNUSED(headers);
    Q_UNUSED(body);
    return Response(0, QJsonObject(), QJsonValue(), "未定义");
}

Response UserController::del(const QJsonObject &headers,
                             const QJsonValue &body) {
    Q_UNUSED(headers);
    Q_UNUSED(body);
    return Response(0, QJsonObject(), QJsonValue(), "未定义");
}
} // namespace My
