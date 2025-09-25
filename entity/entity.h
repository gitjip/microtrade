#ifndef ENTITY_H
#define ENTITY_H

#include "entity_global.h"
#include <QJsonObject>

class ENTITY_EXPORT Entity
{
public:
    Entity();
    // @interface
    // Entity(const QJsonObject &jsonObj);
    virtual ~Entity();
    virtual operator QJsonObject() const = 0;
};

#endif // ENTITY_H
