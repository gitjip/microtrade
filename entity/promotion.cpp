#include "promotion.h"
#include <QDateTime>

Promotion::Promotion() {}

Promotion::Promotion(const qint64 &id, const QDateTime &createdAt,
                     const QDateTime &removedAt, const QDateTime &startAt,
                     const QDateTime &endAt, Strategy strategy,
                     double threshold, double value, const QString &description)
    : Entity(id, createdAt, removedAt), m_startAt(startAt), m_endAt(endAt),
    m_strategy(strategy), m_threshold(threshold), m_value(value),
    m_description(description) {}

Promotion Promotion::fromJson(const QJsonObject &json) {
    Promotion promotion;
    promotion.initFromJson(json);
    return promotion;
}

QJsonObject Promotion::toJson() const {
    QJsonObject json = Entity::toJson();
    if (m_startAt.isValid()) {
        json["startAt"] = m_startAt.toString(Qt::ISODate);
    }
    if (m_endAt.isValid()) {
        json["endAt"] = m_endAt.toString(Qt::ISODate);
    }
    if (m_strategy != Strategy::Null) {
        json["strategy"] = strategyToString(m_strategy);
    }
    if (m_threshold != -1) {
        json["threshold"] = m_threshold;
    }
    if (m_value != -1) {
        json["value"] = m_value;
    }
    if (!m_description.isEmpty()) {
        json["description"] = m_description;
    }
    return json;
}

void Promotion::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_startAt = QDateTime::fromString(json["startAt"].toString(), Qt::ISODate);
    m_endAt = QDateTime::fromString(json["endAt"].toString(), Qt::ISODate);
    m_strategy = stringToStrategy(json["strategy"].toString());
    m_threshold = json["threshold"].toDouble(-1);
    m_value = json["value"].toDouble(-1);
    m_description = json["description"].toString();
}

QString Promotion::strategyToString(Strategy strategy) {
    switch (strategy) {
    case Strategy::Null:
        return "null";
    case Strategy::PercentageDiscount:
        return "percentage_discount";
    case Strategy::FixedAmountDiscount:
        return "fixed_amount_discount";
    case Strategy::BuyXGetYFree:
        return "buy_x_get_y_free";
    case Strategy::FreeShipping:
        return "free_shipping";
    case Strategy::FinalPrice:
        return "final_price";
    default:
        return "null";
    }
}

Promotion::Strategy Promotion::stringToStrategy(const QString &strategyString) {
    if (strategyString == "null" || strategyString.isEmpty())
        return Strategy::Null;
    else if (strategyString == "percentage_discount")
        return Strategy::PercentageDiscount;
    else if (strategyString == "fixed_amount_discount")
        return Strategy::FixedAmountDiscount;
    else if (strategyString == "buy_x_get_y_free")
        return Strategy::BuyXGetYFree;
    else if (strategyString == "free_shipping")
        return Strategy::FreeShipping;
    else if (strategyString == "final_price")
        return Strategy::FinalPrice;
    else
        return Strategy::Null;
}

bool Promotion::operator<(const Promotion &promotion) const {
    return m_id < promotion.m_id;
}

QDateTime Promotion::startAt() const { return m_startAt; }

QDateTime Promotion::endAt() const { return m_endAt; }

Promotion::Strategy Promotion::strategy() const { return m_strategy; }

double Promotion::threshold() const { return m_threshold; }

double Promotion::value() const { return m_value; }

QString Promotion::description() const { return m_description; }

bool Promotion::isActive() const {
    QDateTime now = QDateTime::currentDateTime();
    // qDebug() << Q_FUNC_INFO << now;
    return now >= m_startAt && now <= m_endAt && m_removedAt.isNull();
}
