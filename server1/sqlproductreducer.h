#ifndef SQLPRODUCTREDUCER_H
#define SQLPRODUCTREDUCER_H

#include "sqllocalserver.h"
#include "product.h"

class SqlProductReducer : public SqlLocalServer
{
public:
    SqlProductReducer();
    QMap<Product, qint64> exec(const QMap<Product,qint64> &quantityMap);
};

#endif // SQLPRODUCTREDUCER_H
