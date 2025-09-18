#ifndef GOODS_H
#define GOODS_H

#include "models_global.h"
#include <QString>
#include <QtGlobal>

namespace My {
class MODELS_EXPORT Goods {
public:
    Goods();

    enum class Category {};

private:
    int id;
    QString name;
    QString description;
    double price;
    int stock;
    Category category;
};
} // namespace My

#endif // GOODS_H
