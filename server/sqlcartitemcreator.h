#ifndef SQLCARTITEMCREATOR_H
#define SQLCARTITEMCREATOR_H

#include "sqllocalserver.h"
#include "cartitem.h"
#include "cart.h"
#include "product.h"

class SqlCartItemCreator : public SqlLocalServer
{
public:
    SqlCartItemCreator();
    CartItem exec(const Cart &cart, const Product &product);
};

#endif // SQLCARTITEMCREATOR_H
