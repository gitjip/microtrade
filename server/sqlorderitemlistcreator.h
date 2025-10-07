#ifndef SQLORDERITEMLISTCREATOR_H
#define SQLORDERITEMLISTCREATOR_H

#include "sqllocalserver.h"
#include "product.h"

class SqlOrderItemListCreator : public SqlLocalServer
{
public:
    SqlOrderItemListCreator();
    bool exec(qint64 orderId, const QMap<Product, qint64> &quantityMap);
};

#endif // SQLORDERITEMLISTCREATOR_H
