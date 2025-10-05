#include "orderitem.h"
#include <QtGlobal>

OrderItem::OrderItem() {}

OrderItem::OrderItem(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
                     const qint64 &orderId, const qint64 &productId,
                     qint64 quantity, double cost)
    : Entity(id, createdAt, removedAt), m_orderId(orderId), m_productId(productId),
    m_quantity(quantity), m_cost(cost) {}

OrderItem OrderItem::fromJson(const QJsonObject &json) {
    OrderItem orderItem;
    orderItem.initFromJson(json);
    return orderItem;
}

QJsonObject OrderItem::toJson() const {
    QJsonObject json = Entity::toJson();

    if (m_orderId != -1) {
        json["orderId"] = m_orderId;
    }
    if (m_productId != -1) {
        json["productId"] = m_productId;
    }
    if (m_quantity != -1) {
        json["quantity"] = m_quantity;
    }
    if (m_cost != -1) {
        json["cost"] = m_cost;
    }

    return json;
}

void OrderItem::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_orderId = json["orderId"].toInteger(-1);
    m_productId = json["productId"].toInteger(-1);
    m_quantity = json["quantity"].toInteger(-1);
    m_cost = json["cost"].toDouble(-1);
}

qint64 OrderItem::orderId() const { return m_orderId; }
qint64 OrderItem::productId() const { return m_productId; }
qint64 OrderItem::quantity() const { return m_quantity; }
double OrderItem::cost() const { return m_cost; }
