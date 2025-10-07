#ifndef SQLORDERITEMCREATOR_H
#define SQLORDERITEMCREATOR_H

#include "sqllocalserver.h"

class SqlOrderItemCreator : public SqlLocalServer {
public:
    SqlOrderItemCreator();
    qint64 exec(qint64 orderId, qint64 productId, qint64 quantity, double cost);
};

#endif // SQLORDERITEMCREATOR_H
