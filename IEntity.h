#ifndef IENTITY_H
#define IENTITY_H

#include "oopcore.h"

#define INTERFACE_Entity { \
    void* (*Meta)(IEntity*); \
};

INTERFACE(Entity)
INIT();

#endif // IENTITY_H
