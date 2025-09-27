#include "cartitem.h"

CartItem::CartItem() {}

CartItem::CartItem(const QString &id, const QString &cartId, const QString &productId,
                   qint64 quantity, bool isDeleted)
    : m_id(id), m_cartId(cartId), m_productId(productId),
    m_quantity(quantity), m_isDeleted(isDeleted) {}

CartItem::CartItem(const QJsonObject &jsonObj)
    : m_id(jsonObj[toString(Attribute::Id)].toString()),
    m_cartId(jsonObj[toString(Attribute::CartId)].toString()),
    m_productId(jsonObj[toString(Attribute::ProductId)].toString()),
    m_quantity(jsonObj[toString(Attribute::Quantity)].toInt()),
    m_isDeleted(jsonObj[toString(Attribute::IsDeleted)].toBool()) {}

QString CartItem::toString(Attribute attribute) {
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
    return QJsonObject{{toString(Attribute::Id), m_id},
                       {toString(Attribute::CartId), m_cartId},
                       {toString(Attribute::ProductId), m_productId},
                       {toString(Attribute::Quantity), m_quantity},
                       {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString CartItem::id() const { return m_id; }

QString CartItem::cartId() const { return m_cartId; }

QString CartItem::productId() const { return m_productId; }

qint64 CartItem::quantity() const { return m_quantity; }

bool CartItem::isDeleted() const { return m_isDeleted; }
