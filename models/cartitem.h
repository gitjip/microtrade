#ifndef CARTITEM_H
#define CARTITEM_H

#include "models_global.h"

namespace My {
class MODELS_EXPORT CartItem {
public:
    CartItem();

private:
    int id;
    int cartId;
    int goodsId;
    int quantity;
};
} // namespace My

#endif // CARTITEM_H
