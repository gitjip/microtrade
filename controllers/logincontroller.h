#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "controller.h"

namespace My {
class CONTROLLERS_EXPORT LoginController : public Controller {
    Q_OBJECT
public:
    LoginController(QObject *parent=nullptr);
    Response post(const Headers &headers, const QJsonValue &body) override;
};
} // namespace My

#endif // LOGINCONTROLLER_H
