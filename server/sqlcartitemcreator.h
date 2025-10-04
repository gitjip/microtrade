#ifndef SQLCARTITEMCREATOR_H
#define SQLCARTITEMCREATOR_H

#include "sqllocalserver.h"
#include "cartitem.h"
#include "cart.h"
#include "product.h"

/**
 * @brief create cartItem with cartId and productId, especially on user adding a product to cart
 */
class SqlCartItemCreator : public SqlLocalServer
{
public:
    SqlCartItemCreator();
    CartItem exec(const Cart &cart, const Product &product);
};

#endif // SQLCARTITEMCREATOR_H
