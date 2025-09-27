#include "order.h"

Order::Order() {}

QString Order::toString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::UserId:
        return "user_id";
    case Attribute::Cost:
        return "cost";
    case Attribute::Status:
        return "status";
    case Attribute::CreatedAt:
        return "created_at";
    case Attribute::CancelledAt:
        return "deleted_at";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

QString Order::toString(Status status){
    switch(status){
    case Status::Accepted:
        return "accepted";
    case Status::Returned:
        return "returned";
    case Status::Cancelled:
        return "cancelled";
    case Status::Pending:
        return "pending";
    case Status::Unaccepted:
        return "unaccepted";
    default:
        return "";
    }
}

Order::operator QJsonObject() const {
    return QJsonObject{{toString(Attribute::Id), m_id},
                       {toString(Attribute::UserId), m_userId},
                       {toString(Attribute::Cost), m_cost},
                       {toString(Attribute::Status), toString(m_status)},
                       {toString(Attribute::CreatedAt), m_createdAt.toString()},
                       {toString(Attribute::UserId), m_cancelledAt.toString()},
                       {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString Order::id() const { return m_id; }

QString Order::userId() const { return m_userId; }

double Order::cost() const { return m_cost; }

Order::Status Order::status() const { return m_status; }

QDateTime Order::createdAt() const { return m_createdAt; }

QDateTime Order::cancelledAt() const { return m_cancelledAt; }

bool Order::isDeleted() const { return m_isDeleted; }
