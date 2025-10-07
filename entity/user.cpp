#include "user.h"

User::User() {}

User::User(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
           const QString &username, const QString &passwordHash, const QUrl &avatarUrl)
    : Entity(id, createdAt, removedAt), m_username(username),
    m_passwordHash(passwordHash), m_avatarUrl(avatarUrl) {}

User User::fromJson(const QJsonObject &json) {
    User user;
    user.initFromJson(json);
    return user;
}

QJsonObject User::toJson() const {
    QJsonObject json = Entity::toJson();

    if (!m_username.isEmpty()) {
        json["username"] = m_username;
    }
    if (!m_passwordHash.isEmpty()) {
        json["passwordHash"] = m_passwordHash;
    }
    if (!m_avatarUrl.isEmpty()) {
        json["avatarUrl"] = m_avatarUrl.toString();
    }

    return json;
}

void User::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_username = json["username"].toString();
    m_passwordHash = json["passwordHash"].toString();
    m_avatarUrl = QUrl(json["avatarUrl"].toString());
}

QString User::username() const { return m_username; }

QString User::passwordHash() const { return m_passwordHash; }

QUrl User::avatarUrl() const { return m_avatarUrl; }
