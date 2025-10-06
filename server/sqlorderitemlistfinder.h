#ifndef SQLORDERITEMLISTFINDER_H
#define SQLORDERITEMLISTFINDER_H

#include "sqllocalserver.h"
#include "orderitem.h"

class SqlOrderItemListFinder : public SqlLocalServer
{
public:
    SqlOrderItemListFinder();
    QList<OrderItem> exec(qint64 orderId);
};

#endif // SQLORDERITEMLISTFINDER_H
