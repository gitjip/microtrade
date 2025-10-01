#include "orderitem.h"

OrderItem::OrderItem() {}

OrderItem::OrderItem(const QString &id, const QString &orderId,
                     const QString &productId, qint64 quantity, double cost,
                     bool isDeleted)
    : m_id(id), m_orderId(orderId), m_productId(productId),
    m_quantity(quantity), m_cost(cost), m_isDeleted(isDeleted) {}

OrderItem::OrderItem(const QJsonObject &jsonObj)
    : m_id(jsonObj[attributeToString(Attribute::Id)].toString()),
    m_orderId(jsonObj[attributeToString(Attribute::OrderId)].toString()),
    m_productId(jsonObj[attributeToString(Attribute::ProductId)].toString()),
    m_quantity(jsonObj[attributeToString(Attribute::Quantity)].toInt()),
    m_cost(jsonObj[attributeToString(Attribute::Cost)].toDouble()),
    m_isDeleted(jsonObj[attributeToString(Attribute::IsDeleted)].toBool()) {}

QString OrderItem::attributeToString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::OrderId:
        return "order_id";
    case Attribute::ProductId:
        return "product_id";
    case Attribute::Quantity:
        return "quantity";
    case Attribute::Cost:
        return "cost";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

OrderItem::operator QJsonObject() const {
    return QJsonObject{{attributeToString(Attribute::Id), m_id},
                       {attributeToString(Attribute::OrderId), m_orderId},
                       {attributeToString(Attribute::ProductId), m_productId},
                       {attributeToString(Attribute::Quantity), m_quantity},
                       {attributeToString(Attribute::Cost), m_cost},
                       {attributeToString(Attribute::IsDeleted), m_isDeleted}};
}

QString OrderItem::id() const { return m_id; }

QString OrderItem::orderId() const { return m_orderId; }

QString OrderItem::productId() const { return m_productId; }

qint64 OrderItem::quantity() const { return m_quantity; }

double OrderItem::cost() const { return m_cost; }

bool OrderItem::isDeleted() const { return m_isDeleted; }

bool OrderItem::isValid() const { return !m_id.isEmpty(); }
