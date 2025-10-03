#ifndef ORDER_H
#define ORDER_H

#include "entity.h"

class ENTITY_EXPORT Order : public Entity {
public:
    enum class Status { Pending, Cancelled, Accepted, Unaccepted, Returned };

    Order();
    Order(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
          const qint64 &userId, double cost, Status status);
    static Order fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;
    static QString statusToString(Status status);
    static Status stringToStatus(const QString &statusString);

public:
    qint64 userId() const;
    double cost() const;
    Status status() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_userId = 0;
    double m_cost = 0;
    Status m_status = Status::Pending;
};

#endif // ORDER_H
