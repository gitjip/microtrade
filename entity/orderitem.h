#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "entity.h"

class ENTITY_EXPORT OrderItem : public Entity {
public:
    OrderItem();
    OrderItem(const qint64 &id, const QDateTime &createdAt,
              const QDateTime &removedAt, const qint64 &orderId,
              const qint64 &productId, qint64 quantity, double cost);
    static OrderItem fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

public:
    qint64 orderId() const;
    qint64 productId() const;
    qint64 quantity() const;
    double cost() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_orderId = -1;
    qint64 m_productId = -1;
    qint64 m_quantity = -1;
    double m_cost = qQNaN();
};

#endif // ORDERITEM_H
