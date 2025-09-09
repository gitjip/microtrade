#ifndef RESPONSER_H
#define RESPONSER_H

#include "mylib_global.h"
#include "request.h"
#include "response.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

namespace My {
class MYLIB_EXPORT Responser : public QObject {
    Q_OBJECT
public:
    explicit Responser(QObject *parent = nullptr);
    virtual Response response(const Request &request) = 0;

signals:
};
} // namespace My

#endif // RESPONSER_H
