#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "controller.h"

namespace My {
class UserController : public Controller {
public:
    explicit UserController(QObject *parent = nullptr);
    virtual Response post(const QJsonObject &headers, const QJsonValue &body) override;
};
} // namespace My

#endif // USERCONTROLLER_H
