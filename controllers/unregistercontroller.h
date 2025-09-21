#ifndef UNREGISTERCONTROLLER_H
#define UNREGISTERCONTROLLER_H

#include "controller.h"

namespace My {
class UnregisterController : public Controller {
    Q_OBJECT
public:
    explicit UnregisterController(QObject *parent = nullptr);
    Response post(const Headers &headers, const Body &body);
};
} // namespace My

#endif // UNREGISTERCONTROLLER_H
