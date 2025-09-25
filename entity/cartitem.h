#ifndef CARTITEM_H
#define CARTITEM_H

#include "entity.h"

class CartItem : public Entity
{
public:
    CartItem();

private:
    QString m_id;
    QString m_cartId;
    QString m_productId;
    qint64 m_quantity = 0;
    bool m_isDeleted = false;
};

#endif // CARTITEM_H
