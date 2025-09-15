#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controllers_global.h"
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
    Response send(const QString &method, const QJsonObject &headers,
                  const QJsonValue &body);
    virtual Response get(const QJsonObject &headers, const QJsonValue &body) = 0;
    virtual Response post(const QJsonObject &headers, const QJsonValue &body) = 0;
    virtual Response put(const QJsonObject &headers, const QJsonValue &body) = 0;
    virtual Response del(const QJsonObject &headers, const QJsonValue &body) = 0;

signals:

protected:
    QSqlDatabase db;
};
} // namespace My

#endif // CONTROLLER_H
