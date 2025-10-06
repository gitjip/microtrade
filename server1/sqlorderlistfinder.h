#ifndef SQLORDERLISTFINDER_H
#define SQLORDERLISTFINDER_H

#include "sqllocalserver.h"
#include "order.h"

class SqlOrderListFinder : public SqlLocalServer
{
public:
    SqlOrderListFinder();
    QList<Order> exec(qint64 userId);
};

#endif // SQLORDERLISTFINDER_H
