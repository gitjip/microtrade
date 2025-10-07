#include "entity.h"
#include <cmath>

Entity::Entity() {}

Entity::Entity(qint64 id, const QDateTime &createdAt,
               const QDateTime &removedAt)
    : m_id(id), m_createdAt(createdAt), m_removedAt(removedAt),
    m_isNull(false) {}

Entity::~Entity() {}

Entity Entity::fromJson(const QJsonObject &json) {
    Entity entity;
    entity.initFromJson(json);
    return entity;
}

QJsonObject Entity::toJson() const {
    QJsonObject json;
    if (m_id != -1) {
        json["id"] = m_id;
    }
    if (m_createdAt.isValid()) {
        json["createdAt"] = m_createdAt.toString();
    }
    if (m_removedAt.isValid()) {
        json["removedAt"] = m_removedAt.toString();
    }
    return json;
}

void Entity::initFromJson(const QJsonObject &json) {
    m_id = json["id"].toInteger(-1);
    m_createdAt = QDateTime::fromString(json["createdAt"].toString());
    m_removedAt = QDateTime::fromString(json["removedAt"].toString());
}

qint64 Entity::id() const { return m_id; }

QDateTime Entity::createdAt() const { return m_createdAt; }

QDateTime Entity::removedAt() const { return m_removedAt; }

bool Entity::isNull() const { return m_isNull; }
