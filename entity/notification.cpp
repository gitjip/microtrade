#include "notification.h"

Notification::Notification() {}

QString Notification::id() const { return m_id; }

QString Notification::userId() const { return m_userId; }

QString Notification::content() const { return m_content; }

QDateTime Notification::createdAt() const { return m_createdAt; }

QDateTime Notification::deletedAt() const { return m_deletedAt; }

bool Notification::isDeleted() const { return m_isDeleted; }
