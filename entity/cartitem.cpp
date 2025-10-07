#include "cartitem.h"

CartItem::CartItem() {}

CartItem::CartItem(qint64 id, QDateTime createdAt, QDateTime removedAt,
                   qint64 cartId, qint64 productId, qint64 quantity)
    : Entity(id, createdAt, removedAt), m_cartId(cartId),
    m_productId(productId), m_quantity(quantity) {}

CartItem CartItem::fromJson(const QJsonObject &json) {
    CartItem cartItem;
    cartItem.initFromJson(json);
    return cartItem;
}

QJsonObject CartItem::toJson() const {
    QJsonObject json = Entity::toJson();

    if (m_cartId != -1) {
        json["cartId"] = m_cartId;
    }
    if (m_productId != -1) {
        json["productId"] = m_productId;
    }
    if (m_quantity != -1) {
        json["quantity"] = m_quantity;
    }

    return json;
}

void CartItem::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_cartId = json["cartId"].toInteger();
    m_productId = json["productId"].toInteger();
    m_quantity = json["quantity"].toInteger();
}

qint64 CartItem::cartId() const { return m_cartId; }
qint64 CartItem::productId() const { return m_productId; }
qint64 CartItem::quantity() const { return m_quantity; }
