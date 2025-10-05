#include "product.h"
#include <QtGlobal>

Product::Product() {}

Product::Product(const qint64 &id, const QDateTime &createdAt,
                 const QDateTime &removedAt, const QString &name,
                 const QString &description, double price, qint64 stock,
                 Category category, const QUrl &imageUrl)
    : Entity(id, createdAt, removedAt), m_name(name),
    m_description(description), m_price(price), m_stock(stock),
    m_category(category), m_imageUrl(imageUrl) {}

Product Product::fromJson(const QJsonObject &json) {
    Product product;
    product.initFromJson(json);
    return product;
}

QJsonObject Product::toJson() const {
    QJsonObject json = Entity::toJson();

    if (!m_name.isEmpty()) {
        json["name"] = m_name;
    }
    if (!m_description.isEmpty()) {
        json["description"] = m_description;
    }
    if (m_price != -1) {
        json["price"] = m_price;
    }
    if (m_stock != -1) {
        json["stock"] = m_stock;
    }
    if (m_category != Category::Null) {
        json["category"] = categoryToString(m_category);
    }
    if (!m_imageUrl.isEmpty()) {
        json["imageUrl"] = m_imageUrl.toString();
    }

    return json;
}

void Product::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_name = json["name"].toString();
    m_description = json["description"].toString();
    m_price = json["price"].toDouble(-1);
    m_stock = json["stock"].toInteger(-1);
    m_category = stringToCategory(json["category"].toString());
    m_imageUrl = QUrl(json["imageUrl"].toString());
}

QString Product::categoryToString(Category category) {
    switch (category) {
    case Category::Null:
        return "null";
    case Category::Clothes:
        return "clothes";
    case Category::Electronic:
        return "electronic";
    case Category::Food:
        return "food";
    case Category::Furniture:
        return "furniture";
    case Category::Tool:
        return "tool";
    default:
        return "null";
    }
}

Product::Category Product::stringToCategory(const QString &categoryString) {
    if (categoryString == "null" || categoryString.isEmpty())
        return Category::Null;
    else if (categoryString == "food")
        return Category::Food;
    else if (categoryString == "clothes")
        return Category::Clothes;
    else if (categoryString == "furniture")
        return Category::Furniture;
    else if (categoryString == "tool")
        return Category::Tool;
    else if (categoryString == "electronic")
        return Category::Electronic;
    else
        return Category::Null;
}

bool Product::operator<(const Product &product) const {
    return m_id < product.m_id;
}

QString Product::name() const { return m_name; }
QString Product::description() const { return m_description; }
double Product::price() const { return m_price; }
qint64 Product::stock() const { return m_stock; }
Product::Category Product::category() const { return m_category; }
QUrl Product::imageUrl() const { return m_imageUrl; }
