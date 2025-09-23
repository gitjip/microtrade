#ifndef GOODS_H
#define GOODS_H

#include "models_global.h"
#include <QJsonObject>
#include <QString>

namespace My {
class MODELS_EXPORT Goods {
public:
    Goods(int id, const QString &name, const QString &description, double price,
          int stock, const QString& category);
    Goods(const QJsonObject &object);
    operator QJsonObject() const;

public:
    int id;
    QString name;
    QString description;
    double price;
    int stock;
    QString category;
};
} // namespace My

#endif // GOODS_H
