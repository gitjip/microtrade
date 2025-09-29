#ifndef SQLUSERIDFINDER_H
#define SQLUSERIDFINDER_H

#include <sqlserver.h>

class SqlUserIdFinder : public SqlServer
{
public:
    SqlUserIdFinder();
    QString exec(const QString &username, const QString &password);
};

#endif // SQLUSERIDFINDER_H
