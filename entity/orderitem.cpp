#include "orderitem.h"

OrderItem::OrderItem() {}

QString OrderItem::id() const { return m_id; }

QString OrderItem::orderId() const { return m_orderId; }

QString OrderItem::productId() const { return m_productId; }

qint64 OrderItem::quantity() const { return m_quantity; }

double OrderItem::cost() const { return m_cost; }

bool OrderItem::isDeleted() const { return m_isDeleted; }
