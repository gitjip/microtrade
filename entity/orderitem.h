#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "entity.h"

class OrderItem : public Entity
{
public:
    OrderItem();

private:
    QString m_id;
    QString m_orderId;
    QString m_productId;
    qint64 m_quantity = 0;
    double m_cost = 0;
    bool m_isDeleted = false;
};

#endif // ORDERITEM_H
