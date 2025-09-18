#include "unregistercontroller.h"
#include <QSqlQuery>

namespace My {
UnregisterController::UnregisterController(QObject *parent)
    : Controller{parent} {}

Response UnregisterController::post(const Headers &headers, const Body &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    int userId = body.toInt();
    query.prepare("SELECT * FROM users WHERE rowid = :id AND active = 1");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        return Response(500, Headers(), Body(), "error occurred when quering user");
    }
    if (!query.next()) {
        return Response(404, Headers(), Body(), "user not found");
    }
    query.prepare("UPDATE users SET active = 0 WHERE rowid = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        return Response(500, Headers(), Body(), "error occurred when adding user");
    }
    return Response(200, Headers(), Body(), "success");
}
} // namespace My
