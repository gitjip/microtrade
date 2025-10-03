#ifndef CART_H
#define CART_H

#include "entity.h"
#include <QDateTime>

class ENTITY_EXPORT Cart : public Entity {
public:
    Cart();
    Cart(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
         const qint64 &userId);
    static Cart fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

public:
    qint64 userId() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_userId = 0;
};

#endif // CART_H
