#ifndef SQLORDERMODIFIER_H
#define SQLORDERMODIFIER_H

#include <QObject>
#include <QSqlDatabase>
#include "sqlserver.h"

class SqlOrderModifier : public QObject
{
    Q_OBJECT
public:
    explicit SqlOrderModifier(QObject *parent = nullptr);
    bool cancelOrder(qint64 orderId, qint64 userId);

private:
    QSqlDatabase m_db;
}; 

#endif // SQLORDERMODIFIER_H