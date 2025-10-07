#include "productpromotionrelation.h"

ProductPromotionRelation::ProductPromotionRelation() {}

ProductPromotionRelation::ProductPromotionRelation(const qint64 &id, const QDateTime &createdAt,
                                                   const QDateTime &removedAt, const qint64 &productId,
                                                   const qint64 &promotionId)
    : Entity(id, createdAt, removedAt), m_productId(productId), m_promotionId(promotionId) {}

ProductPromotionRelation ProductPromotionRelation::fromJson(const QJsonObject &json) {
    ProductPromotionRelation relation;
    relation.initFromJson(json);
    return relation;
}

QJsonObject ProductPromotionRelation::toJson() const {
    QJsonObject json = Entity::toJson();
    if (m_productId != -1) {
        json["productId"] = m_productId;
    }
    if (m_promotionId != -1) {
        json["promotionId"] = m_promotionId;
    }
    return json;
}

void ProductPromotionRelation::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_productId = json["productId"].toInteger(-1);
    m_promotionId = json["promotionId"].toInteger(-1);
}

bool ProductPromotionRelation::operator<(const ProductPromotionRelation &relation) const {
    return m_id < relation.m_id;
}

qint64 ProductPromotionRelation::productId() const {
    return m_productId;
}

qint64 ProductPromotionRelation::promotionId() const {
    return m_promotionId;
}
