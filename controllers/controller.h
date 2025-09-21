#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controllers_global.h"
#include "mylib_constants.h"
#include "response.h"
#include <QObject>
#include <QSqlDatabase>
#include <QString>

namespace My {
class CONTROLLERS_EXPORT Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();
    virtual Response post(const Headers &headers, const Body &body) = 0;
    Response send(const QString &method, const Headers &headers,
                  const Body &body);

signals:

protected:
    QSqlDatabase db;
};
} // namespace My

#endif // CONTROLLER_H
