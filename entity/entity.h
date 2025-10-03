#ifndef ENTITY_H
#define ENTITY_H

#include "entity_global.h"
#include <QJsonObject>

class ENTITY_EXPORT Entity {
public:
    Entity();
    Entity(qint64 id, const QDateTime &createdAt, const QDateTime &removedAt);
    virtual ~Entity();
    static Entity fromJson(const QJsonObject &json);
    virtual QJsonObject toJson() const;

public:
    qint64 id() const;
    QDateTime createdAt() const;
    QDateTime removedAt() const;
    bool isNull() const;

protected:
    virtual void initFromJson(const QJsonObject &json);

protected:
    qint64 m_id = 0;
    QDateTime m_createdAt;
    QDateTime m_removedAt;
    bool m_isNull = true;
};

#endif // ENTITY_H
