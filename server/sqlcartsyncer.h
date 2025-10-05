#ifndef SQLCARTSYNCER_H
#define SQLCARTSYNCER_H

#include "sqllocalserver.h"
#include "cartitem.h"
#include "cart.h"

class SqlCartSyncer : public SqlLocalServer
{
public:
    SqlCartSyncer();
    bool exec(const Cart &cart, const QList<CartItem> &cartItemList);
};

#endif // SQLCARTSYNCER_H
