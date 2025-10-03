#include "user.h"

User::User() {}

User::User(const qint64 &id, const QString &username, const QString &password,
           const QUrl &avatarUrl, const QDateTime &registeredAt,
           const QDateTime &unregisteredAt, bool isDeleted)
    : m_id(id), m_username(username), m_passwordHash(password),
    m_avatarUrl(avatarUrl), m_createdAt(registeredAt),
    m_removedAt(unregisteredAt), m_isRemoved(isDeleted) {}

User::User(const QJsonObject &jsonObj)
    : m_id(jsonObj["id"].toInteger()),
    m_username(jsonObj["username"].toString()),
    m_passwordHash(jsonObj["password_hash"].toString()),
    m_avatarUrl(QUrl(jsonObj["avatar_url"].toString())),
    m_createdAt(QDateTime::fromString(jsonObj["created_at"].toString())),
    m_removedAt(QDateTime::fromString(jsonObj["removed_at"].toString())),
    m_isRemoved(jsonObj["is_removed"].toBool()) {}

User::operator QJsonObject() const {
    return QJsonObject{{"id", m_id},
                       {"username", m_username},
                       {"password_hash", m_passwordHash},
                       {"avatar_url", m_avatarUrl.toString()},
                       {"created_at", m_createdAt.toString()},
                       {"removed_at", m_removedAt.toString()},
                       {"is_removed", m_isRemoved}};
}

qint64 User::id() const { return m_id; }

QString User::username() const { return m_username; }

QString User::passwordHash() const { return m_passwordHash; }

QUrl User::avatarUrl() const { return m_avatarUrl; }

QDateTime User::createdAt() const { return m_createdAt; }

QDateTime User::removedAt() const { return m_removedAt; }

bool User::isRemoved() const { return m_isRemoved; }

bool User::isValid() const { return m_isValid; }
