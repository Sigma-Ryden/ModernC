#ifndef IHUMAN_H
#define IHUMAN_H

#include "IEntity.h"

#define INTERFACE_Human { \
    void (*PrintName)(void*); \
    int (*GetAge)(void*); \
};

INTERFACE(Human)
    IMPLEMENTS(Entity);
INIT();

#endif // IHUMAN_H
