#ifndef CART_H
#define CART_H

#include "entity.h"

class Cart : public Entity
{
public:
    Cart();

private:
    QString m_id;
    QString m_userId;
    bool m_isDeleted = false;
};

#endif // CART_H
