#ifndef SQLUSERCREATOR_H
#define SQLUSERCREATOR_H

#include "sqllocalserver.h"
#include "user.h"

/**
 * @brief create a user with its full information, especially on user ready for registering
 */
class SqlUserCreator : public SqlLocalServer
{
public:
    SqlUserCreator();
    User exec(const User &user);
};

#endif // SQLUSERCREATOR_H
