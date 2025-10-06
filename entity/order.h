#ifndef ORDER_H
#define ORDER_H

#include "entity.h"

class ENTITY_EXPORT Order : public Entity {
public:
    enum class Status {
        Null = 0,
        Pending,
        Cancelled,
        Accepted,
        Unaccepted,
        Returned
    };

    Order();
    Order(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
          const qint64 &userId, double cost, Status status);
    static Order fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;
    static QString statusToString(Status status);
    static Status stringToStatus(const QString &statusString);

public:
    bool operator<(const Order &order) const;

public:
    qint64 userId() const;
    double cost() const;
    Status status() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_userId = -1;
    double m_cost = -1;
    Status m_status = Status::Null;
};

#endif // ORDER_H
