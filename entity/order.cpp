#include "order.h"
#include <QtGlobal>

Order::Order() {}

Order::Order(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
             const qint64 &userId, double cost, Status status)
    : Entity(id, createdAt, removedAt), m_userId(userId), m_cost(cost), m_status(status) {}

Order Order::fromJson(const QJsonObject &json) {
    Order order;
    order.initFromJson(json);
    return order;
}

QJsonObject Order::toJson() const {
    QJsonObject json = Entity::toJson();

    if (m_userId != -1) {
        json["userId"] = m_userId;
    }
    if (!qIsNaN(m_cost)) {
        json["cost"] = m_cost;
    }
    if (m_status != Status::Null) {
        json["status"] = statusToString(m_status);
    }

    return json;
}

void Order::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_userId = json["userId"].toInteger(-1);
    m_cost = json["cost"].toDouble(qQNaN());
    m_status = stringToStatus(json["status"].toString());
}

QString Order::statusToString(Status status) {
    switch (status) {
    case Status::Null: return "null";
    case Status::Accepted: return "accepted";
    case Status::Returned: return "returned";
    case Status::Cancelled: return "cancelled";
    case Status::Pending: return "pending";
    case Status::Unaccepted: return "unaccepted";
    default: return "null";
    }
}

Order::Status Order::stringToStatus(const QString &statusString) {
    if (statusString == "null" || statusString.isEmpty()) return Status::Null;
    else if (statusString == "accepted") return Status::Accepted;
    else if (statusString == "returned") return Status::Returned;
    else if (statusString == "cancelled") return Status::Cancelled;
    else if (statusString == "pending") return Status::Pending;
    else if (statusString == "unaccepted") return Status::Unaccepted;
    else return Status::Null;
}

qint64 Order::userId() const { return m_userId; }
double Order::cost() const { return m_cost; }
Order::Status Order::status() const { return m_status; }
