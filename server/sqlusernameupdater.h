#ifndef SQLUSERNAMEUPDATER_H
#define SQLUSERNAMEUPDATER_H

#include "sqllocalserver.h"

class SqlUsernameUpdater : public SqlLocalServer
{
public:
    SqlUsernameUpdater();
    bool exec(qint64 userId, const QString &username);
};

#endif // SQLUSERNAMEUPDATER_H
