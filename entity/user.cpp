#include "user.h"

User::User() {}

User::User(const QString &id, const QString &username, const QString &password,
           const QUrl &avatarUrl, const QDateTime &registeredAt,
           const QDateTime &unregisteredAt, bool isDeleted)
    : m_id(id), m_username(username), m_password(password),
    m_avatarUrl(avatarUrl), m_registeredAt(registeredAt),
    m_unregisteredAt(unregisteredAt), m_isDeleted(isDeleted) {}

User::User(const QJsonObject &jsonObj)
    : m_id(jsonObj[toString(Attribute::Id)].toString()),
    m_username(jsonObj[toString(Attribute::Username)].toString()),
    m_password(jsonObj[toString(Attribute::Password)].toString()),
    m_avatarUrl(QUrl(jsonObj[toString(Attribute::AvatarUrl)].toString())),
    m_registeredAt(QDateTime::fromString(
          jsonObj[toString(Attribute::RegisteredAt)].toString())),
    m_unregisteredAt(QDateTime::fromString(
          jsonObj[toString(Attribute::UnregisteredAt)].toString())),
    m_isDeleted(jsonObj[toString(Attribute::IsDeleted)].toBool()) {}

QString User::toString(Attribute attribute) {
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
                       {toString(Attribute::Id), m_id},
        {toString(Attribute::Username), m_username},
        {toString(Attribute::Password), m_password},
        {toString(Attribute::AvatarUrl), m_avatarUrl.toString()},
        {toString(Attribute::RegisteredAt), m_registeredAt.toString()},
        {toString(Attribute::UnregisteredAt), m_unregisteredAt.toString()},
        {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString User::id() const { return m_id; }

QString User::username() const { return m_username; }

QString User::password() const { return m_password; }

QUrl User::avatarUrl() const { return m_avatarUrl; }

QDateTime User::registeredAt() const { return m_registeredAt; }

QDateTime User::unregisteredAt() const { return m_unregisteredAt; }

bool User::isDeleted() const { return m_isDeleted; }
