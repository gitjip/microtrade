#include "logincontroller.h"

#include "user.h"
#include <QSqlQuery>

namespace My {
LoginController::LoginController(QObject *parent) : Controller(parent) {}

Response LoginController::post(const Headers &headers, const Body &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    User user(body.toObject());
    if (user.username.isEmpty() || user.password.isEmpty()) {
        return Response(400, Headers(), Body(),
                        "username and password cannot be empty");
    }
    query.prepare(
        "SELECT rowid, * FROM users WHERE username = :username AND password = "
        ":password;");
    query.bindValue(":username", user.username);
    query.bindValue(":password", user.password);
    if (!query.exec()) {
        return Response(500, Headers(), Body(), "error occurred when quering user");
    }
    if (!query.next()) {
        return Response(404, Headers(), Body(), "user not found");
    }
    User responseUser(query.value("rowid").toInt(),
                      query.value("username").toString(),
                      query.value("password").toString());
    return Response(200, Headers(), QJsonObject(responseUser), "");
}
} // namespace My
