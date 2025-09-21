#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include "controller.h"

namespace My {
class CONTROLLERS_EXPORT RegisterController : public Controller {
    Q_OBJECT
public:
    RegisterController(QObject *parent);
    Response post(const Headers &headers, const Body &body) override;
};
} // namespace My

#endif // REGISTERCONTROLLER_H
