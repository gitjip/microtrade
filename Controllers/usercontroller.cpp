#include "usercontroller.h"
#include "user.h"
#include <QSqlError>
#include <QSqlQuery>

namespace My {
UserController::UserController(QObject *parent) : Controller{parent} {}

Response UserController::post(const QJsonObject &headers,
                              const QJsonValue &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    int userId=body["id"].toInt();
    query.prepare("SELECT * FROM users WHERE rowid = :id;");
    query.bindValue(":id", userId);
    if(!query.exec()){
        return Response(500, Headers(), Body(), "My::UserController::post: error occurred when quering user");
    }
    if(!query.next()){
        return Response(404, Headers(), Body(), "My::UserController::post: user not found");
    }
    My::User responseUser(userId, query.value("username").toString(), query.value("password").toString());
    return Response(200, Headers(), QJsonObject(responseUser), "success");
}
} // namespace My
