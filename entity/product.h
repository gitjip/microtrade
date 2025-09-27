#ifndef PRODUCT_H
#define PRODUCT_H

#include "entity.h"
#include <QDateTime>

class Product : public Entity
{
public:
    enum class Attribute {
        Id,
        Name,
        Description,
        Price,
        Stock,
        Category,
        ImageUrl,
        ListedAt,
        DelistedAt,
        IsDeleted
    };
    enum class Category { Food, Clothes, Furniture, Tool, Electronic };

public:
    Product();
    static QString toString(Attribute attribute);
    static QString toString(Category category);
    operator QJsonObject() const override;

public:
    QString id() const;
    QString name() const;
    QString description() const;
    double price() const;
    qint64 stock() const;
    Category category() const;
    QUrl imageUrl() const;
    QDateTime listedAt() const;
    QDateTime delistedAt() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_name;
    QString m_description;
    double m_price = 0;
    qint64 m_stock = 0;
    Category m_category;
    QUrl m_imageUrl;
    QDateTime m_listedAt;
    QDateTime m_delistedAt;
    bool m_isDeleted = false;
};

#endif // PRODUCT_H
