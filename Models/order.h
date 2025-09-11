#ifndef ORDER_H
#define ORDER_H

#include <QList>
#include <QtGlobal>
#include <QTime>

class Order
{
public:
    Order();

public:
    enum class Status{};

private:
    int id;
    int userId;
    double cost;
    QTime createTime;
    Status status;
    QList<int> OrderItemIdList;
};

#endif // ORDER_H
