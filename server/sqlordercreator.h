#ifndef SQLORDERCREATOR_H
#define SQLORDERCREATOR_H

#include "sqllocalserver.h"
#include "user.h"

class SqlOrderCreator : public SqlLocalServer
{
public:
    SqlOrderCreator();
    qint64 exec(const User &user, double cost);
};

#endif // SQLORDERCREATOR_H
