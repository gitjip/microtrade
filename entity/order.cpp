#include "order.h"

Order::Order() {}

Order::Order(const QString &id, const QString &userId, double cost,
             Status status, const QDateTime &createdAt,
             const QDateTime &cancelledAt, bool isDeleted)
    : m_id(id), m_userId(userId), m_cost(cost), m_status(status),
    m_createdAt(createdAt), m_cancelledAt(cancelledAt),
    m_isDeleted(isDeleted) {}

Order::Order(const QJsonObject &jsonObj)
    : m_id(jsonObj[attributeToString(Attribute::Id)].toString()),
    m_userId(jsonObj[attributeToString(Attribute::UserId)].toString()),
    m_cost(jsonObj[attributeToString(Attribute::Cost)].toDouble()),
    m_status(
          stringToStatus(jsonObj[attributeToString(Attribute::Status)].toString())),
    m_createdAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::CreatedAt)].toString())),
    m_cancelledAt(QDateTime::fromString(
          jsonObj[attributeToString(Attribute::CancelledAt)].toString())),
    m_isDeleted(jsonObj[attributeToString(Attribute::IsDeleted)].toBool()) {}

QString Order::attributeToString(Attribute attribute) {
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

QString Order::statusToString(Status status) {
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

Order::Status Order::stringToStatus(const QString &statusString) {
    if (statusString == "accepted") {
        return Status::Accepted;
    } else if (statusString == "returned") {
        return Status::Returned;
    } else if (statusString == "cancelled") {
        return Status::Cancelled;
    } else if (statusString == "pending") {
        return Status::Pending;
    } else if (statusString == "unaccepted") {
        return Status::Unaccepted;
    } else {
        return Status::Pending; // default
    }
}

Order::operator QJsonObject() const {
    return QJsonObject{
        {attributeToString(Attribute::Id), m_id},
        {attributeToString(Attribute::UserId), m_userId},
        {attributeToString(Attribute::Cost), m_cost},
        {attributeToString(Attribute::Status), statusToString(m_status)},
        {attributeToString(Attribute::CreatedAt), m_createdAt.toString()},
        {attributeToString(Attribute::CancelledAt), m_cancelledAt.toString()},
        {attributeToString(Attribute::IsDeleted), m_isDeleted}};
}

QString Order::id() const { return m_id; }

QString Order::userId() const { return m_userId; }

double Order::cost() const { return m_cost; }

Order::Status Order::status() const { return m_status; }

QDateTime Order::createdAt() const { return m_createdAt; }

QDateTime Order::cancelledAt() const { return m_cancelledAt; }

bool Order::isDeleted() const { return m_isDeleted; }
