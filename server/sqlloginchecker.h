#ifndef SQLLOGINCHECKER_H
#define SQLLOGINCHECKER_H

#include "sqllocalserver.h"
#include "user.h"

class SqlLoginChecker : public SqlLocalServer
{
public:
    SqlLoginChecker();
    User exec(const User &user);
};

#endif // SQLLOGINCHECKER_H
