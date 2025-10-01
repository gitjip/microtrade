#include "user.h"

User::User() {}

User::User(const QString &id, const QString &username, const QString &password,
           const QUrl &avatarUrl, const QDateTime &registeredAt,
           const QDateTime &unregisteredAt, bool isDeleted)
    : m_id(id), m_username(username), m_password(password),
    m_avatarUrl(avatarUrl), m_registeredAt(registeredAt),
    m_unregisteredAt(unregisteredAt), m_isDeleted(isDeleted) {}

User::User(const QJsonObject &jsonObj)
    : m_id(jsonObj[attributeToString(Attribute::Id)].toString()),
    m_username(jsonObj[attributeToString(Attribute::Username)].toString()),
    m_password(jsonObj[attributeToString(Attribute::Password)].toString()),
    m_avatarUrl(QUrl(jsonObj[attributeToString(Attribute::AvatarUrl)].toString())),
    m_registeredAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::RegisteredAt)].toString())),
    m_unregisteredAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::UnregisteredAt)].toString())),
    m_isDeleted(jsonObj[attributeToString(Attribute::IsDeleted)].toBool()) {}

QString User::attributeToString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::Username:
        return "username";
    case Attribute::Password:
        return "password";
    case Attribute::AvatarUrl:
        return "avatar_url";
    case Attribute::RegisteredAt:
        return "registered_at";
    case Attribute::UnregisteredAt:
        return "unregistered_at";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

User::operator QJsonObject() const {
    return QJsonObject{
                       {attributeToString(Attribute::Id), m_id},
        {attributeToString(Attribute::Username), m_username},
        {attributeToString(Attribute::Password), m_password},
        {attributeToString(Attribute::AvatarUrl), m_avatarUrl.toString()},
        {attributeToString(Attribute::RegisteredAt), m_registeredAt.toString()},
        {attributeToString(Attribute::UnregisteredAt), m_unregisteredAt.toString()},
        {attributeToString(Attribute::IsDeleted), m_isDeleted}};
}

QString User::id() const { return m_id; }

QString User::username() const { return m_username; }

QString User::password() const { return m_password; }

QUrl User::avatarUrl() const { return m_avatarUrl; }

QDateTime User::registeredAt() const { return m_registeredAt; }

QDateTime User::unregisteredAt() const { return m_unregisteredAt; }

bool User::isDeleted() const { return m_isDeleted; }

bool User::isValid() const { return !m_id.isEmpty(); }
