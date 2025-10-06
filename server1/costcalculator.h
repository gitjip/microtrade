#ifndef COSTCALCULATOR_H
#define COSTCALCULATOR_H

#include "product.h"

class CostCalculator
{
public:
    CostCalculator();
    static double calculate(const QMap<Product, qint64> &quantityMap);
};

#endif // COSTCALCULATOR_H
