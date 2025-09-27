#include "cart.h"

Cart::Cart() {}

Cart::Cart(const QString &id, const QString &userId, const QDateTime &createdAt,
           const QDateTime &deletedAt, bool isDeleted)
    : m_id(id), m_userId(userId), m_createdAt(createdAt),
    m_deletedAt(deletedAt), m_isDeleted(isDeleted) {}

Cart::Cart(const QJsonObject &jsonObj)
    : m_id(jsonObj[toString(Attribute::Id)].toString()),
    m_userId(jsonObj[toString(Attribute::UserId)].toString()),
    m_createdAt(QDateTime::fromString(
          jsonObj[toString(Attribute::CreatedAt)].toString())),
    m_deletedAt(QDateTime::fromString(
          jsonObj[toString(Attribute::DeletedAt)].toString())),
    m_isDeleted(jsonObj[toString(Attribute::IsDeleted)].toBool()) {}

QString Cart::toString(Attribute attribute) {
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
    return QJsonObject{{toString(Attribute::Id), m_id},
                       {toString(Attribute::UserId), m_userId},
                       {toString(Attribute::CreatedAt), m_createdAt.toString()},
                       {toString(Attribute::DeletedAt), m_deletedAt.toString()},
                       {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString Cart::id() const { return m_id; }

QString Cart::userId() const { return m_userId; }

QDateTime Cart::createdAt() const { return m_createdAt; }

QDateTime Cart::deletedAt() const { return m_deletedAt; }

bool Cart::isDeleted() const { return m_isDeleted; }
