#ifndef SQLPROMOTIONLISTFINDER_H
#define SQLPROMOTIONLISTFINDER_H

#include "sqllocalserver.h"
#include "promotion.h"

class SqlPromotionListFinder : public SqlLocalServer
{
public:
    SqlPromotionListFinder();
    QList<Promotion> exec();
};

#endif // SQLPROMOTIONLISTFINDER_H
