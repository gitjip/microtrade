#ifndef SQLPASSWORDUPDATER_H
#define SQLPASSWORDUPDATER_H

#include "sqllocalserver.h"

class SqlPasswordUpdater : public SqlLocalServer
{
public:
    SqlPasswordUpdater();
    bool exec(qint64 userId, const QString &oldPasswordHash, const QString &newPasswordHash);
};

#endif // SQLPASSWORDUPDATER_H
