#ifndef SQLPRODUCTLISTFINDER_H
#define SQLPRODUCTLISTFINDER_H

#include <sqlserver.h>
#include "product.h"

class SqlProductListFinder : public SqlServer
{
public:
    SqlProductListFinder();
    QList<Product> exec();
};

#endif // SQLPRODUCTLISTFINDER_H
