#ifndef CARTITEM_H
#define CARTITEM_H

#include "Models_global.h"

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
