#ifndef SQLSERVER_H
#define SQLSERVER_H

#include "sqlserver_global.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class SQLSERVER_EXPORT SqlServer
{
public:
    SqlServer();
    bool open(const QString &databaseName);

protected:
    QSqlDatabase db;
};

#endif // SQLSERVER_H
