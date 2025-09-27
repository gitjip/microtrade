#include "orderitem.h"

OrderItem::OrderItem() {}

OrderItem::OrderItem(const QString &id, const QString &orderId,
                     const QString &productId, qint64 quantity, double cost,
                     bool isDeleted)
    : m_id(id), m_orderId(orderId), m_productId(productId),
    m_quantity(quantity), m_cost(cost), m_isDeleted(isDeleted) {}

OrderItem::OrderItem(const QJsonObject &jsonObj)
    : m_id(jsonObj[toString(Attribute::Id)].toString()),
    m_orderId(jsonObj[toString(Attribute::OrderId)].toString()),
    m_productId(jsonObj[toString(Attribute::ProductId)].toString()),
    m_quantity(jsonObj[toString(Attribute::Quantity)].toInt()),
    m_cost(jsonObj[toString(Attribute::Cost)].toDouble()),
    m_isDeleted(jsonObj[toString(Attribute::IsDeleted)].toBool()) {}

QString OrderItem::toString(Attribute attribute) {
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
    return QJsonObject{{toString(Attribute::Id), m_id},
                       {toString(Attribute::OrderId), m_orderId},
                       {toString(Attribute::ProductId), m_productId},
                       {toString(Attribute::Quantity), m_quantity},
                       {toString(Attribute::Cost), m_cost},
                       {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString OrderItem::id() const { return m_id; }

QString OrderItem::orderId() const { return m_orderId; }

QString OrderItem::productId() const { return m_productId; }

qint64 OrderItem::quantity() const { return m_quantity; }

double OrderItem::cost() const { return m_cost; }

bool OrderItem::isDeleted() const { return m_isDeleted; }
