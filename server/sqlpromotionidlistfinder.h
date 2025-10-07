#ifndef SQLPROMOTIONIDLISTFINDER_H
#define SQLPROMOTIONIDLISTFINDER_H

#include "sqllocalserver.h"

class SqlPromotionIdListFinder : public SqlLocalServer
{
public:
    SqlPromotionIdListFinder();
    QList<qint64> exec(qint64 product_id);
};

#endif // SQLPROMOTIONIDLISTFINDER_H
