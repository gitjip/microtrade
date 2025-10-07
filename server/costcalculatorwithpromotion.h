#ifndef COSTCALCULATORWITHPROMOTION_H
#define COSTCALCULATORWITHPROMOTION_H

#include "promotion.h"

class CostCalculatorWithPromotion {
public:
    CostCalculatorWithPromotion();
    static double calculate(double price, qint64 quantity,
                            const QList<Promotion> &promotionList);

private:
    static double calculatePercentageDiscount(double cost, double threshold,
                                              double percentage);
    static double calculateFixedAmountDiscount(double cost, double threshold,
                                               double delta);
};

#endif // COSTCALCULATORWITHPROMOTION_H
