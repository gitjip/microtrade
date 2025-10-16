#include "sqlmonthlycostserver.h"
#include <QDate>
#include <QJsonObject>
#include <QSqlError>

SqlMonthlyCostServer::SqlMonthlyCostServer() {}

double SqlMonthlyCostServer::exec(qint64 userId, int year, int month) {
    QSqlQuery query(db);
    query.prepare("SELECT SUM(cost) FROM orders WHERE user_id=? AND created_at "
                  "BETWEEN ? AND ? AND removed_at IS NULL");
    QDate start_date{year, month, 1};
    QDate end_date{year, month, start_date.daysInMonth()};
    query.addBindValue(userId);
    query.addBindValue(start_date);
    query.addBindValue(end_date);
    qDebug() << Q_FUNC_INFO << query.boundValueNames();
    qDebug() << Q_FUNC_INFO << query.boundValues();
    if (!query.exec() || !query.next()) {
        qDebug() << query.lastError().text();
        return -1;
    }
    double cost = query.value("SUM(cost)").toDouble();
    qDebug() << Q_FUNC_INFO << cost;
    return cost;
}
