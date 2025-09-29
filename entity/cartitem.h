#ifndef CARTITEM_H
#define CARTITEM_H

#include "entity.h"

class ENTITY_EXPORT CartItem : public Entity {
public:
    enum class Attribute { Id, CartId, ProductId, Quantity, IsDeleted };

public:
    CartItem();
    CartItem(const QString &id, const QString &cartId, const QString &productId,
             qint64 quantity, bool isDeleted = false);
    CartItem(const QJsonObject &jsonObj);
    static QString attributeToString(Attribute attribute);
    operator QJsonObject() const override;

public:
    QString id() const;
    QString cartId() const;
    QString productId() const;
    qint64 quantity() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_cartId;
    QString m_productId;
    qint64 m_quantity = 0;
    bool m_isDeleted = false;
};

#endif // CARTITEM_H
