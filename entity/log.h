#ifndef LOG_H
#define LOG_H

#include "entity.h"

class ENTITY_EXPORT Log : public Entity {
public:
    enum class Type { Info, Warning, Error };

    Log();
    Log(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
        Type type, const QString &text);
    static Log fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;
    static QString typeToString(Type type);
    static Type stringToType(const QString &typeString);

public:
    Type type() const;
    QString text() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    Type m_type = Type::Info;
    QString m_text;
};

#endif // LOG_H
