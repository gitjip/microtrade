#ifndef SQLMONTHLYCOSTSERVER_H
#define SQLMONTHLYCOSTSERVER_H

#include "sqllocalserver.h"

class SqlMonthlyCostServer : public SqlLocalServer
{
public:
    SqlMonthlyCostServer();
    double exec(qint64 userId, int year, int month);
};

#endif // SQLMONTHLYCOSTSERVER_H
