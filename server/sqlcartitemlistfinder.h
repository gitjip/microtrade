#ifndef SQLCARTITEMLISTFINDER_H
#define SQLCARTITEMLISTFINDER_H

#include "sqllocalserver.h"
#include "cartitem.h"
#include "cart.h"

class SqlCartItemListFinder : public SqlLocalServer
{
public:
    SqlCartItemListFinder();
    QList<CartItem> exec(const Cart &cart);
};

#endif // SQLCARTITEMLISTFINDER_H
