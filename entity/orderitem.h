#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "entity.h"

class ENTITY_EXPORT OrderItem : public Entity {
public:
    enum class Attribute { Id, OrderId, ProductId, Quantity, Cost, IsDeleted };

public:
    OrderItem();
    OrderItem(const QString &id, const QString &orderId, const QString &productId,
              qint64 quantity, double cost, bool isDeleted = false);
    OrderItem(const QJsonObject &jsonObj);
    static QString attributeToString(Attribute attribute);
    operator QJsonObject() const override;

public:
    QString id() const;
    QString orderId() const;
    QString productId() const;
    qint64 quantity() const;
    double cost() const;
    bool isDeleted() const;
    bool isValid() const;

private:
    QString m_id;
    QString m_orderId;
    QString m_productId;
    qint64 m_quantity = 0;
    double m_cost = 0;
    bool m_isDeleted = false;
};

#endif // ORDERITEM_H
