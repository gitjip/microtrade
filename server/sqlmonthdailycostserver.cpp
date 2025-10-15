#include "sqlmonthdailycostserver.h"
#include <QDate>
#include <QSqlError>

SqlMonthDailyCostServer::SqlMonthDailyCostServer() {}

QJsonArray SqlMonthDailyCostServer::exec(qint64 userId, int year, int month) {
    QSqlQuery query(db);
    query.prepare(
        "SELECT SUM(cost) FROM orders WHERE user_id=:user_id AND created_at "
        "BETWEEN :start AND :end AND removed_at IS NULL");
    QDate startDate{year, month, 1};
    QJsonArray ret;
    for (qsizetype i = 0; i < startDate.daysInMonth(); ++i) {
        QDate currentDate = startDate.addDays(i);
        query.bindValue(":user_id", userId);
        query.bindValue(":start", currentDate);
        query.bindValue(":end", currentDate.addDays(1));
        if (!query.exec() || !query.next()) {
            qDebug() << Q_FUNC_INFO << query.lastError().text();
        }
        QJsonObject dailyCost;
        dailyCost["date"] = currentDate.toString();
        dailyCost["cost"] = query.value("SUM(cost)").toDouble();
        ret.append(dailyCost);
    }
    qDebug() << Q_FUNC_INFO << ret;
    return ret;
}
