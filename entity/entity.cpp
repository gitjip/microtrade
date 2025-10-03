#include "entity.h"

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
    json["id"] = m_id;
    json["createdAt"] = m_createdAt.toString();
    json["removedAt"] = m_removedAt.toString();
    return json;
}

void Entity::initFromJson(const QJsonObject &json) {
    m_id = json["id"].toInteger();
    m_createdAt = QDateTime::fromString(json["createdAt"].toString());
    m_removedAt = QDateTime::fromString(json["removedAt"].toString());
}

qint64 Entity::id() const { return m_id; }

QDateTime Entity::createdAt() const { return m_createdAt; }

QDateTime Entity::removedAt() const { return m_removedAt; }

bool Entity::isNull() const { return m_isNull; }
