#include "goods.h"

namespace My {
Goods::Goods(int id, const QString &name, const QString &description,
             double price, int stock, const QString &category)
    : id(id), name(name), description(description), price(price), stock(stock),
    category(category) {}

Goods::Goods(const QJsonObject &object) {
    id = object["id"].toInt();
    name = object["name"].toString();
    description = object["description"].toString();
    price = object["price"].toDouble();
    stock = object["stock"].toInt();
    category = object["category"].toString();
}

Goods::operator QJsonObject() const {
    QJsonObject res;
    res["id"] = id;
    res["name"] = name;
    res["description"] = description;
    res["price"] = price;
    res["stock"] = stock;
    res["category"] = category;
    return res;
}
} // namespace My
