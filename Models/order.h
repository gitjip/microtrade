#ifndef ORDER_H
#define ORDER_H

#include "models_global.h"
#include <QList>
#include <QTime>
#include <QtGlobal>

namespace My {
class MODELS_EXPORT Order {
public:
    Order();

public:
    enum class Status {};

private:
    int id;
    int userId;
    double cost;
    QTime createTime;
    Status status;
    QList<int> OrderItemIdList;
};
} // namespace My

#endif // ORDER_H
