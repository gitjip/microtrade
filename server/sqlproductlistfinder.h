#ifndef SQLPRODUCTLISTFINDER_H
#define SQLPRODUCTLISTFINDER_H

#include "product.h"
#include "sqllocalserver.h"

/**
 * @brief find all products and return them as a list
 */
class SqlProductListFinder : public SqlLocalServer
{
public:
    SqlProductListFinder();
    QList<Product> exec();
};

#endif // SQLPRODUCTLISTFINDER_H
