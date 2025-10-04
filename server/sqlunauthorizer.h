#ifndef SQLUNAUTHORIZER_H
#define SQLUNAUTHORIZER_H

#include "sqllocalserver.h"
#include "authorization.h"

class SqlUnauthorizer : public SqlLocalServer
{
public:
    SqlUnauthorizer();
    bool exec(const Authorization &authorization);
};

#endif // SQLUNAUTHORIZER_H
