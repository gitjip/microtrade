#ifndef SQLUSERFINDER_H
#define SQLUSERFINDER_H

#include "sqllocalserver.h"
#include "user.h"

/**
 * @brief find a user with its id
 */
class SqlUserFinder : public SqlLocalServer
{
public:
    SqlUserFinder();
    User exec(const User &user);
};

#endif // SQLUSERFINDER_H
