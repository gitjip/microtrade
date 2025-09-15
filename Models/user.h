#ifndef USER_H
#define USER_H

#include "models_global.h"
#include <QString>
#include <QtGlobal>

namespace My {
class MODELS_EXPORT User {
public:
    User(int id, const QString &username, const QString &password);
    virtual ~User();

private:
    int id;
    QString username;
    QString password;
};
} // namespace My

#endif // USER_H
