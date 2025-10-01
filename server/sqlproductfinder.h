#ifndef SQLPRODUCTFINDER_H
#define SQLPRODUCTFINDER_H

#include "product.h"
#include "sqlserver.h"

class SqlProductFinder : public SqlServer
{
public:
    SqlProductFinder();
    Product exec(const QString &productId);
};

#endif // SQLPRODUCTFINDER_H
