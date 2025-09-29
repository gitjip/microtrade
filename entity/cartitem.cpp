#include "cartitem.h"

CartItem::CartItem() {}

CartItem::CartItem(const QString &id, const QString &cartId, const QString &productId,
                   qint64 quantity, bool isDeleted)
    : m_id(id), m_cartId(cartId), m_productId(productId),
    m_quantity(quantity), m_isDeleted(isDeleted) {}

CartItem::CartItem(const QJsonObject &jsonObj)
    : m_id(jsonObj[attributeToString(Attribute::Id)].toString()),
    m_cartId(jsonObj[attributeToString(Attribute::CartId)].toString()),
    m_productId(jsonObj[attributeToString(Attribute::ProductId)].toString()),
    m_quantity(jsonObj[attributeToString(Attribute::Quantity)].toInt()),
    m_isDeleted(jsonObj[attributeToString(Attribute::IsDeleted)].toBool()) {}

QString CartItem::attributeToString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::CartId:
        return "cart_id";
    case Attribute::ProductId:
        return "product_id";
    case Attribute::Quantity:
        return "quantity";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

CartItem::operator QJsonObject() const {
    return QJsonObject{{attributeToString(Attribute::Id), m_id},
                       {attributeToString(Attribute::CartId), m_cartId},
                       {attributeToString(Attribute::ProductId), m_productId},
                       {attributeToString(Attribute::Quantity), m_quantity},
                       {attributeToString(Attribute::IsDeleted), m_isDeleted}};
}

QString CartItem::id() const { return m_id; }

QString CartItem::cartId() const { return m_cartId; }

QString CartItem::productId() const { return m_productId; }

qint64 CartItem::quantity() const { return m_quantity; }

bool CartItem::isDeleted() const { return m_isDeleted; }
