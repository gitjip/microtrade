#ifndef CARTITEM_H
#define CARTITEM_H

#include "entity.h"

class ENTITY_EXPORT CartItem : public Entity {
public:
    CartItem();
    CartItem(qint64 cartId, qint64 productId, qint64 quantity);
    static CartItem fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

private:
    void initFromJson(const QJsonObject &json) override;

public:
    qint64 cartId() const;
    qint64 productId() const;
    qint64 quantity() const;

private:
    qint64 m_cartId;
    qint64 m_productId;
    qint64 m_quantity = 0;
};

#endif // CARTITEM_H
