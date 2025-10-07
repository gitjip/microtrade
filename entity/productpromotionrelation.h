#ifndef PRODUCTPROMOTIONRELATION_H
#define PRODUCTPROMOTIONRELATION_H

#include "entity.h"

class ENTITY_EXPORT ProductPromotionRelation : public Entity {
public:
    ProductPromotionRelation();
    ProductPromotionRelation(const qint64 &id, const QDateTime &createdAt,
                             const QDateTime &removedAt, const qint64 &productId,
                             const qint64 &promotionId);
    static ProductPromotionRelation fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

public:
    bool operator<(const ProductPromotionRelation &relation) const;

public:
    qint64 productId() const;
    qint64 promotionId() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_productId = -1;
    qint64 m_promotionId = -1;
};

#endif // PRODUCTPROMOTIONRELATION_H
