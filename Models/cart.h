#ifndef CART_H
#define CART_H

#include <QList>

class Cart
{
public:
    Cart();

private:
    int id;
    int userId;
    QList<int> cartItemIdList;
};

#endif // CART_H
