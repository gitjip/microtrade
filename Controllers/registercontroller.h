#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include "controller.h"

namespace My {
class CONTROLLERS_EXPORT RegisterController : public Controller {
    Q_OBJECT
public:
    RegisterController(QObject *parent);
    Response post(const QJsonObject &headers, const QJsonValue &body) override;
};
} // namespace My

#endif // REGISTERCONTROLLER_H
