#ifndef ORDER_H
#define ORDER_H

#include "entity.h"
#include <QDateTime>

class Order : public Entity
{
public:
    Order();

private:
    QString m_id;
    QString m_userId;
    double m_cost = 0;
    QDateTime m_createdAt;
    QString m_status;
    bool m_isDeleted = false;
};

#endif // ORDER_H
