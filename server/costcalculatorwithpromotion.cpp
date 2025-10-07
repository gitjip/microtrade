#include "costcalculatorwithpromotion.h"

CostCalculatorWithPromotion::CostCalculatorWithPromotion() {}

double
CostCalculatorWithPromotion::calculate(double price, qint64 quantity,
                                       const QList<Promotion> &promotionList) {
    double firstCost = price * quantity;
    double finalCost = firstCost;
    for (qsizetype i = 0; i < promotionList.count(); ++i) {
        double thisCost = firstCost;
        if (promotionList[i].isActive()) {
            if (promotionList[i].strategy() ==
                Promotion::Strategy::PercentageDiscount) {
                thisCost = calculatePercentageDiscount(
                    firstCost, promotionList[i].threshold(), promotionList[i].value());
            } else if (promotionList[i].strategy() ==
                       Promotion::Strategy::FixedAmountDiscount) {
                thisCost = calculateFixedAmountDiscount(
                    firstCost, promotionList[i].threshold(), promotionList[i].value());
            }
        }
        finalCost = qMin(finalCost, thisCost);
    }
    return finalCost;
}

double CostCalculatorWithPromotion::calculatePercentageDiscount(
    double cost, double threshold, double percentage) {
    return cost > threshold ? cost * percentage : cost;
}

double CostCalculatorWithPromotion::calculateFixedAmountDiscount(
    double cost, double threshold, double delta) {
    return cost > threshold ? cost - delta : cost;
}
