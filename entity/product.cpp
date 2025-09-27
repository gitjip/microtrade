#include "product.h"

Product::Product() {}

Product::Product(const QString &id, const QString &name,
                 const QString &description, double price, qint64 stock,
                 Category category, const QUrl &imageUrl,
                 const QDateTime &listedAt, const QDateTime &delistedAt,
                 bool isDeleted)
    : m_id(id), m_name(name), m_description(description), m_price(price),
    m_stock(stock), m_category(category), m_imageUrl(imageUrl),
    m_listedAt(listedAt), m_delistedAt(delistedAt), m_isDeleted(isDeleted) {}

Product::Product(const QJsonObject &jsonObj)
    : m_id(jsonObj[toString(Attribute::Id)].toString()),
    m_name(jsonObj[toString(Attribute::Name)].toString()),
    m_description(jsonObj[toString(Attribute::Description)].toString()),
    m_price(jsonObj[toString(Attribute::Price)].toDouble()),
    m_stock(jsonObj[toString(Attribute::Stock)].toInt()),
    m_category(toCategory(
          jsonObj[toString(Attribute::Category)].toString())),
    m_imageUrl(QUrl(jsonObj[toString(Attribute::ImageUrl)].toString())),
    m_listedAt(QDateTime::fromString(
          jsonObj[toString(Attribute::ListedAt)].toString())),
    m_delistedAt(QDateTime::fromString(
          jsonObj[toString(Attribute::DelistedAt)].toString())),
    m_isDeleted(jsonObj[toString(Attribute::IsDeleted)].toBool()) {}

QString Product::toString(Attribute attribute) {
    switch (attribute) {
    case Attribute::Id:
        return "id";
    case Attribute::Name:
        return "name";
    case Attribute::Description:
        return "description";
    case Attribute::Price:
        return "price";
    case Attribute::Stock:
        return "stock";
    case Attribute::Category:
        return "category";
    case Attribute::ImageUrl:
        return "image_url";
    case Attribute::ListedAt:
        return "listed_at";
    case Attribute::DelistedAt:
        return "delisted_at";
    case Attribute::IsDeleted:
        return "is_deleted";
    default:
        return "";
    }
}

QString Product::toString(Category category) {
    switch (category) {
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
        return "";
    }
}

Product::Category Product::toCategory(const QString &categoryStr) {
    if (categoryStr == "food") {
        return Category::Food;
    } else if (categoryStr == "clothes") {
        return Category::Clothes;
    } else if (categoryStr == "furniture") {
        return Category::Furniture;
    } else if (categoryStr == "tool") {
        return Category::Tool;
    } else if (categoryStr == "electronic") {
        return Category::Electronic;
    } else {
        return Category::Food; // default
    }
}

Product::operator QJsonObject() const {
    return QJsonObject{{toString(Attribute::Id), m_id},
                       {toString(Attribute::Name), m_name},
                       {toString(Attribute::Description), m_description},
                       {toString(Attribute::Price), m_price},
                       {toString(Attribute::Stock), m_stock},
                       {toString(Attribute::Category), toString(m_category)},
                       {toString(Attribute::ImageUrl), m_imageUrl.toString()},
                       {toString(Attribute::ListedAt), m_listedAt.toString()},
                       {toString(Attribute::DelistedAt), m_delistedAt.toString()},
                       {toString(Attribute::IsDeleted), m_isDeleted}};
}

QString Product::id() const { return m_id; }

QString Product::name() const { return m_name; }

QString Product::description() const { return m_description; }

double Product::price() const { return m_price; }

qint64 Product::stock() const { return m_stock; }

Product::Category Product::category() const { return m_category; }

QUrl Product::imageUrl() const { return m_imageUrl; }

QDateTime Product::listedAt() const { return m_listedAt; }

QDateTime Product::delistedAt() const { return m_delistedAt; }

bool Product::isDeleted() const { return m_isDeleted; }
