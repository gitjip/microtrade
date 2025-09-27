#include "cartitem.h"

CartItem::CartItem() {}

QString CartItem::id() const { return m_id; }

QString CartItem::cartId() const { return m_cartId; }

QString CartItem::productId() const { return m_productId; }

qint64 CartItem::quantity() const { return m_quantity; }

bool CartItem::isDeleted() const { return m_isDeleted; }
