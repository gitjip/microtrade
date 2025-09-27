#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "entity.h"

class OrderItem : public Entity
{
public:
    enum class Attribute { Id, OrderId, ProductId, Quantity, Cost, IsDeleted };

public:
    OrderItem();
    QString toString(Attribute attribute);

public:
    QString id() const;
    QString orderId() const;
    QString productId() const;
    qint64 quantity() const;
    double cost() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_orderId;
    QString m_productId;
    qint64 m_quantity = 0;
    double m_cost = 0;
    bool m_isDeleted = false;
};

#endif // ORDERITEM_H
