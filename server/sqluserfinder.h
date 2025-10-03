#ifndef SQLUSERFINDER_H
#define SQLUSERFINDER_H

#include "sqllocalserver.h"
#include "user.h"

class SqlUserFinder : public SqlLocalServer
{
public:
    SqlUserFinder();
    User exec(const User &user);
};

#endif // SQLUSERFINDER_H
