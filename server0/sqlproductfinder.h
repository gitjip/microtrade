#ifndef SQLPRODUCTFINDER_H
#define SQLPRODUCTFINDER_H

#include "product.h"
#include "sqllocalserver.h"

/**
 * @brief find a product with its id
 */
class SqlProductFinder : public SqlLocalServer
{
public:
    SqlProductFinder();
    Product exec(const Product &product);
};

#endif // SQLPRODUCTFINDER_H
