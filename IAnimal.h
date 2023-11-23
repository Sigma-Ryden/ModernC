#ifndef IANIMAL_H
#define IANIMAL_H

#include "oopcore.h"

#define TYPE_IAnimal { \
    void (*ShowInfo)(void*); \
};

INTERFACE(IAnimal)
INIT()

#endif // IANIMAL_H
