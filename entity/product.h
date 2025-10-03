#ifndef PRODUCT_H
#define PRODUCT_H

#include "entity.h"
#include <QUrl>

class ENTITY_EXPORT Product : public Entity {
public:
    enum class Category {
        Null = 0,
        Food,
        Clothes,
        Furniture,
        Tool,
        Electronic
    };

    Product();
    Product(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
            const QString &name, const QString &description, double price,
            qint64 stock, Category category, const QUrl &imageUrl = QUrl());
    static Product fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;
    static QString categoryToString(Category category);
    static Category stringToCategory(const QString &categoryString);

public:
    QString name() const;
    QString description() const;
    double price() const;
    qint64 stock() const;
    Category category() const;
    QUrl imageUrl() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    QString m_name;
    QString m_description;
    double m_price = qQNaN();
    qint64 m_stock = -1;
    Category m_category = Category::Null;
    QUrl m_imageUrl;
};

#endif // PRODUCT_H
