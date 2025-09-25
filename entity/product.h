#ifndef PRODUCT_H
#define PRODUCT_H

#include "entity.h"

class Product : public Entity
{
public:
    Product();

private:
    QString m_id;
    QString m_name;
    QString m_description;
    double m_price = 0;
    qint64 m_stock = 0;
    QString m_category;
    QString m_imageUrl;
    bool m_isDeleted = false;
};

#endif // PRODUCT_H
