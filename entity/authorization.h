#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "entity.h"

class ENTITY_EXPORT Authorization : public Entity {
public:
    Authorization();
    Authorization(const qint64 &id, const QDateTime &createdAt,
                  const QDateTime &removedAt, const qint64 &userId,
                  const QString &token);
    static Authorization fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

public:
    qint64 userId() const;
    QString token() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_userId = -1;
    QString m_token;
};

#endif // AUTHORIZATION_H
