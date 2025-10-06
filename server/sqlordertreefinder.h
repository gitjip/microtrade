#ifndef SQLORDERTREEFINDER_H
#define SQLORDERTREEFINDER_H

#include "order.h"
#include "orderitem.h"
#include "sqllocalserver.h"

class SqlOrderTreeFinder : public SqlLocalServer {
public:
    SqlOrderTreeFinder();
    QMap<Order, QList<OrderItem>> exec(qint64 userId);
};

#endif // SQLORDERTREEFINDER_H
