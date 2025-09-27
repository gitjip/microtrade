#include "user.h"

User::User() {}

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
    return QJsonObject{{toString(Attribute::Id), m_id},
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
