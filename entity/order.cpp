#include "order.h"

Order::Order() {}

QString Order::id() const { return m_id; }

QString Order::userId() const { return m_userId; }

double Order::cost() const { return m_cost; }

Order::Status Order::status() const { return m_status; }

QDateTime Order::createdAt() const { return m_createdAt; }

QDateTime Order::cancelledAt() const { return m_cancelledAt; }

bool Order::isDeleted() const { return m_isDeleted; }
