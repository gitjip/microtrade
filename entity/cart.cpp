#include "cart.h"

Cart::Cart() {}

QString Cart::id() const { return m_id; }

QString Cart::userId() const { return m_userId; }

QDateTime Cart::createdAt() const { return m_createdAt; }

QDateTime Cart::deletedAt() const { return m_deletedAt; }

bool Cart::isDeleted() const { return m_isDeleted; }
