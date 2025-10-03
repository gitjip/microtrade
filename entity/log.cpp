#include "log.h"

Log::Log() {}

Log::Log(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
         Type type, const QString &text)
    : Entity(id, createdAt, removedAt), m_type(type), m_text(text) {}

Log Log::fromJson(const QJsonObject &json) {
    Log log;
    log.initFromJson(json);
    return log;
}

QJsonObject Log::toJson() const {
    QJsonObject json = Entity::toJson();
    json["type"] = typeToString(m_type);
    json["text"] = m_text;
    return json;
}

void Log::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_type = stringToType(json["type"].toString());
    m_text = json["text"].toString();
}

QString Log::typeToString(Type type) {
    switch (type) {
    case Type::Info: return "info";
    case Type::Warning: return "warning";
    case Type::Error: return "error";
    default: return "info";
    }
}

Log::Type Log::stringToType(const QString &typeString) {
    if (typeString == "info") return Type::Info;
    else if (typeString == "warning") return Type::Warning;
    else if (typeString == "error") return Type::Error;
    else return Type::Info;
}

Log::Type Log::type() const { return m_type; }
QString Log::text() const { return m_text; }
