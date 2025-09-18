#include "registercontroller.h"

#include "mylib_constants.h"
#include "user.h"
#include <QSqlQuery>

namespace My {
RegisterController::RegisterController(QObject *parent) : Controller(parent) {}

Response RegisterController::post(const Headers &headers, const Body &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    User user(body.toObject());
    if (user.username.isEmpty() || user.password.isEmpty()) {
        return Response(400, Headers(), Body(),
                        "username and password cannot be empty");
    }
    query.prepare("SELECT * FROM users WHERE username = :username AND active = 1");
    query.bindValue(":username", body["username"].toString());
    if (!query.exec()) {
        return Response(500, Headers(), Body(), "error occurred when quering user");
    }
    if (query.next()) {
        return Response(403, Headers(), Body(), "user already exists");
    }
    query.prepare("INSERT INTO users (username, password, active) VALUES (:username, "
                  ":password, 1)");
    query.bindValue(":username", user.username);
    query.bindValue(":password", user.password);
    if (!query.exec()) {
        return Response(500, Headers(), Body(), "error occurred when adding user");
    }
    return Response(200, Headers(), Body(), "success");
}
} // namespace My
