#ifndef SQLMONTHDAILYCOSTSERVER_H
#define SQLMONTHDAILYCOSTSERVER_H

#include "sqllocalserver.h"
#include <QJsonObject>
#include <QJsonArray>

class SqlMonthDailyCostServer : public SqlLocalServer
{
public:
    SqlMonthDailyCostServer();
    QJsonArray exec(qint64 userId, int year, int month);
};

#endif // SQLMONTHDAILYCOSTSERVER_H
