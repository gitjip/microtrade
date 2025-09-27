#include "notification.h"

Notification::Notification() {}

QString Notification::toString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::UserId:
        return "user_id";
    case Attribute::Content:
        return "content";
    case Attribute::CreatedAt:
        return "created_at";
    case Attribute::DeletedAt:
        return "deleted_at";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

Notification::operator QJsonObject() const {
    return QJsonObject{{toString(Attribute::Id), m_id},
                       {toString(Attribute::UserId), m_userId},
                       {toString(Attribute::Content), m_content},
                       {toString(Attribute::CreatedAt), m_createdAt.toString()},
                       {toString(Attribute::DeletedAt), m_deletedAt.toString()},
                       {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString Notification::id() const { return m_id; }

QString Notification::userId() const { return m_userId; }

QString Notification::content() const { return m_content; }

QDateTime Notification::createdAt() const { return m_createdAt; }

QDateTime Notification::deletedAt() const { return m_deletedAt; }

bool Notification::isDeleted() const { return m_isDeleted; }
