#ifndef ENTITY_H
#define ENTITY_H

#include "entity_global.h"
#include <QJsonObject>

class ENTITY_EXPORT Entity
{
public:
    Entity();
    virtual ~Entity();
    virtual operator QJsonObject() const = 0;
};

#endif // ENTITY_H
