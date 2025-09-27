#include "product.h"

Product::Product() {}

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

QString Product::toString(Category category){
    switch (category){
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
