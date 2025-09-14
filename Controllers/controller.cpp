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
        qDebug() << "未开启数据库";
    }else{
        qDebug() << "已开启数据库";
    }
}

Controller::~Controller() {}

Response Controller::send(const QString &method, const QJsonObject &headers,
                          const QJsonValue &body) {
    if (method == "get") {
        return get(headers, body);
    } else if (method == "post") {
        return post(headers, body);
    } else if (method == "put") {
        return put(headers, body);
    } else if (method == "delete") {
        return del(headers, body);
    } else {
        return Response(1, QJsonObject(), QJsonValue(), "invalid method");
    }
}
} // namespace My
