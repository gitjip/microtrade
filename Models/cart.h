#ifndef CART_H
#define CART_H

#include "Models_global.h"
#include <QList>

namespace My {
class MODELS_EXPORT Cart {
public:
    Cart();

private:
    int id;
    int userId;
    QList<int> cartItemIdList;
};
} // namespace My

#endif // CART_H
