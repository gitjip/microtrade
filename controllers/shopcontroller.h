#ifndef SHOPCONTROLLER_H
#define SHOPCONTROLLER_H

#include "controller.h"

namespace My {
class ShopController : public Controller {
    Q_OBJECT
public:
    ShopController(QObject *parent = nullptr);
    Response post(const Headers &headers, const Body &body) override;
};
} // namespace My

#endif // SHOPCONTROLLER_H
