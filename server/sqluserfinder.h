#ifndef SQLUSERFINDER_H
#define SQLUSERFINDER_H

#include <sqlserver.h>
#include "user.h"

class SqlUserFinder : public SqlServer
{
public:
    SqlUserFinder();
    User exec(const QString &userId);
};

#endif // SQLUSERFINDER_H
