#ifndef PROMOTION_H
#define PROMOTION_H

#include "entity.h"
#include <QDateTime>

class ENTITY_EXPORT Promotion : public Entity {
public:
    enum class Strategy {
        Null = 0,
        PercentageDiscount,
        FixedAmountDiscount,
        BuyXGetYFree,
        FreeShipping,
        FinalPrice
    };

    Promotion();
    Promotion(const qint64 &id, const QDateTime &createdAt,
              const QDateTime &removedAt, const QDateTime &startAt,
              const QDateTime &endAt, Strategy strategy, double threshold,
              double value, const QString &description = QString());
    static Promotion fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;
    static QString strategyToString(Strategy strategy);
    static Strategy stringToStrategy(const QString &strategyString);

public:
    bool operator<(const Promotion &promotion) const;

public:
    QDateTime startAt() const;
    QDateTime endAt() const;
    Strategy strategy() const;
    double threshold() const;
    double value() const;
    QString description() const;
    bool isActive() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    QDateTime m_startAt;
    QDateTime m_endAt;
    Strategy m_strategy = Strategy::Null;
    double m_threshold = -1;
    double m_value = -1;
    QString m_description;
};

#endif // PROMOTION_H
