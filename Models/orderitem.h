#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "models_global.h"

namespace My {
class MODELS_EXPORT OrderItem {
public:
    OrderItem();

private:
    int id;
    int orderId;
    int goodsId;
    int quantity;
    double price;
};
} // namespace My

#endif // ORDERITEM_H
