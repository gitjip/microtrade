#include "costcalculator.h"

CostCalculator::CostCalculator() {}

double CostCalculator::calculate(const QMap<Product, qint64> &quantityMap) {
    double cost = 0;
    QMapIterator it(quantityMap);
    while (it.hasNext()) {
        it.next();
        cost += it.key().price() * it.value();
    }
    return cost;
}
