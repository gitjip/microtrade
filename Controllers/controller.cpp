#include "controller.h"

namespace My {
Controller::Controller(QObject *parent) : QObject(parent) {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName("my.db");
    if (!db.open()) {
        qDebug() << "database open failed";
    }
}

Controller::~Controller() {}

Response Controller::send(const QString &method, const Headers &headers,
                          const Body &body) {
    if (method == "post") {
        return post(headers, body);
    }
    return Response(0, Headers(), Body(), "undefined method");
}

} // namespace My
