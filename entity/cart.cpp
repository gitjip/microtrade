#include "cart.h"

Cart::Cart() {}

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
