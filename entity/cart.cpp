#include "cart.h"

Cart::Cart() {}

Cart::Cart(const QString &id, const QString &userId, const QDateTime &createdAt,
           const QDateTime &deletedAt, bool isDeleted)
    : m_id(id), m_userId(userId), m_createdAt(createdAt),
    m_deletedAt(deletedAt), m_isDeleted(isDeleted) {}

Cart::Cart(const QJsonObject &jsonObj)
    : m_id(jsonObj[attributeToString(Attribute::Id)].toString()),
    m_userId(jsonObj[attributeToString(Attribute::UserId)].toString()),
    m_createdAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::CreatedAt)].toString())),
    m_deletedAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::DeletedAt)].toString())),
    m_isDeleted(jsonObj[attributeToString(Attribute::IsDeleted)].toBool()) {}

QString Cart::attributeToString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::UserId:
        return "user_id";
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

Cart::operator QJsonObject() const {
    return QJsonObject{{attributeToString(Attribute::Id), m_id},
                       {attributeToString(Attribute::UserId), m_userId},
                       {attributeToString(Attribute::CreatedAt), m_createdAt.toString()},
                       {attributeToString(Attribute::DeletedAt), m_deletedAt.toString()},
                       {attributeToString(Attribute::IsDeleted), m_isDeleted}};
}

QString Cart::id() const { return m_id; }

QString Cart::userId() const { return m_userId; }

QDateTime Cart::createdAt() const { return m_createdAt; }

QDateTime Cart::deletedAt() const { return m_deletedAt; }

bool Cart::isDeleted() const { return m_isDeleted; }
