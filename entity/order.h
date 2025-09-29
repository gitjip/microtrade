#ifndef ORDER_H
#define ORDER_H

#include "entity.h"
#include <QDateTime>

class ENTITY_EXPORT Order : public Entity {
public:
    enum class Attribute {
        Id,
        UserId,
        Cost,
        Status,
        CreatedAt,
        CancelledAt,
        IsDeleted
    };
    enum class Status { Pending, Cancelled, Accepted, Unaccepted, Returned };

public:
    Order();
    Order(const QString &id, const QString &userId, double cost, Status status,
          const QDateTime &createdAt, const QDateTime &cancelledAt,
          bool isDeleted = false);
    Order(const QJsonObject &jsonObj);
    static QString attributeToString(Attribute attribute);
    static QString statusToString(Status status);
    static Status stringToStatus(const QString &statusString);
    operator QJsonObject() const override;

public:
    QString id() const;
    QString userId() const;
    double cost() const;
    Status status() const;
    QDateTime createdAt() const;
    QDateTime cancelledAt() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_userId;
    double m_cost = 0;
    Status m_status;
    QDateTime m_createdAt;
    QDateTime m_cancelledAt;
    bool m_isDeleted = false;
};

#endif // ORDER_H
