#include "notification.h"

Notification::Notification() {}

Notification::Notification(const QString &id, const QString &userId,
                           const QString &content, const QDateTime &createdAt,
                           const QDateTime &deletedAt, bool isDeleted)
    : m_id(id), m_userId(userId), m_content(content), m_createdAt(createdAt),
    m_deletedAt(deletedAt), m_isDeleted(isDeleted) {}

Notification::Notification(const QJsonObject &jsonObj)
    : m_id(jsonObj[attributeToString(Attribute::Id)].toString()),
    m_userId(jsonObj[attributeToString(Attribute::UserId)].toString()),
    m_content(jsonObj[attributeToString(Attribute::Content)].toString()),
    m_createdAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::CreatedAt)].toString())),
    m_deletedAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::DeletedAt)].toString())),
    m_isDeleted(jsonObj[attributeToString(Attribute::IsDeleted)].toBool()) {}

QString Notification::attributeToString(Attribute attribute) {
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
    return QJsonObject{{attributeToString(Attribute::Id), m_id},
                       {attributeToString(Attribute::UserId), m_userId},
                       {attributeToString(Attribute::Content), m_content},
                       {attributeToString(Attribute::CreatedAt), m_createdAt.toString()},
                       {attributeToString(Attribute::DeletedAt), m_deletedAt.toString()},
                       {attributeToString(Attribute::IsDeleted), m_isDeleted}};
}

QString Notification::id() const { return m_id; }

QString Notification::userId() const { return m_userId; }

QString Notification::content() const { return m_content; }

QDateTime Notification::createdAt() const { return m_createdAt; }

QDateTime Notification::deletedAt() const { return m_deletedAt; }

bool Notification::isDeleted() const { return m_isDeleted; }

bool Notification::isValid() const { return !m_id.isEmpty(); }
