#include "user.h"

User::User() {}

QString User::id() const { return m_id; }

QString User::username() const { return m_username; }

QString User::password() const { return m_password; }

QUrl User::avatarUrl() const { return m_avatarUrl; }

QDateTime User::registeredAt() const { return m_registeredAt; }

QDateTime User::unregisteredAt() const { return m_unregisteredAt; }

bool User::isDeleted() const { return m_isDeleted; }
