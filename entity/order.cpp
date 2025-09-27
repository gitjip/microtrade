#include "order.h"

Order::Order() {}

Order::Order(const QString &id, const QString &userId, double cost,
             Status status, const QDateTime &createdAt,
             const QDateTime &cancelledAt, bool isDeleted)
    : m_id(id), m_userId(userId), m_cost(cost), m_status(status),
    m_createdAt(createdAt), m_cancelledAt(cancelledAt),
    m_isDeleted(isDeleted) {}

Order::Order(const QJsonObject &jsonObj)
    : m_id(jsonObj[toString(Attribute::Id)].toString()),
    m_userId(jsonObj[toString(Attribute::UserId)].toString()),
    m_cost(jsonObj[toString(Attribute::Cost)].toDouble()),
    m_status(
          toStatus(jsonObj[toString(Attribute::Status)].toString())),
    m_createdAt(QDateTime::fromString(
          jsonObj[toString(Attribute::CreatedAt)].toString())),
    m_cancelledAt(QDateTime::fromString(
          jsonObj[toString(Attribute::CancelledAt)].toString())),
    m_isDeleted(jsonObj[toString(Attribute::IsDeleted)].toBool()) {}

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
        return "cancelled_at";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

QString Order::toString(Status status) {
    switch (status) {
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

Order::Status Order::toStatus(const QString &statusStr) {
    if (statusStr == "accepted") {
        return Status::Accepted;
    } else if (statusStr == "returned") {
        return Status::Returned;
    } else if (statusStr == "cancelled") {
        return Status::Cancelled;
    } else if (statusStr == "pending") {
        return Status::Pending;
    } else if (statusStr == "unaccepted") {
        return Status::Unaccepted;
    } else {
        return Status::Pending; // default
    }
}

Order::operator QJsonObject() const {
    return QJsonObject{
                       {toString(Attribute::Id), m_id},
        {toString(Attribute::UserId), m_userId},
        {toString(Attribute::Cost), m_cost},
        {toString(Attribute::Status), toString(m_status)},
        {toString(Attribute::CreatedAt), m_createdAt.toString()},
        {toString(Attribute::CancelledAt), m_cancelledAt.toString()},
        {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString Order::id() const { return m_id; }

QString Order::userId() const { return m_userId; }

double Order::cost() const { return m_cost; }

Order::Status Order::status() const { return m_status; }

QDateTime Order::createdAt() const { return m_createdAt; }

QDateTime Order::cancelledAt() const { return m_cancelledAt; }

bool Order::isDeleted() const { return m_isDeleted; }
