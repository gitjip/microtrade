#include "cart.h"

Cart::Cart() {}

Cart::Cart(const qint64 &id, const QDateTime &createdAt,
           const QDateTime &removedAt, const qint64 &userId)
    : Entity(id, createdAt, removedAt), m_userId(userId) {}

Cart Cart::fromJson(const QJsonObject &json) {
    Cart cart;
    cart.initFromJson(json);
    return cart;
}

QJsonObject Cart::toJson() const {
    QJsonObject json = Entity::toJson();
    json["userId"] = m_userId;
    return json;
}

void Cart::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_userId = json["userId"].toInteger();
}

qint64 Cart::userId() const { return m_userId; }
