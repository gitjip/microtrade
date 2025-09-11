#ifndef GOODS_H
#define GOODS_H

#include <QtGlobal>
#include <QString>

class Goods
{
public:
    Goods();

enum class Category{};

private:
    int id;
    QString name;
    QString description;
    double price;
    int stock;
    Category category;
};

#endif // GOODS_H
