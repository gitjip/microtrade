#ifndef USER_H
#define USER_H

#include "models_global.h"
#include <QJsonObject>
#include <QString>

namespace My {
class MODELS_EXPORT User {
public:
    User(int id, const QString &username, const QString &password, bool active);
    User(const QJsonObject &object);
    virtual ~User();
    operator QJsonObject() const;

public:
    int id;
    QString username;
    QString password;
    bool active;
};
} // namespace My

#endif // USER_H
