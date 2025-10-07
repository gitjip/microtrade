#ifndef SQLPROMOTIONFINDER_H
#define SQLPROMOTIONFINDER_H

#include "sqllocalserver.h"
#include "promotion.h"

class SqlPromotionFinder : public SqlLocalServer
{
public:
    SqlPromotionFinder();
    Promotion exec(qint64 promotionId);
};

#endif // SQLPROMOTIONFINDER_H
