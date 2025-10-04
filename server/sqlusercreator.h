#ifndef SQLUSERCREATOR_H
#define SQLUSERCREATOR_H

#include "sqllocalserver.h"
#include "user.h"

class SqlUserCreator : public SqlLocalServer
{
public:
    SqlUserCreator();
    User exec(const User &user);
};

#endif // SQLUSERCREATOR_H
