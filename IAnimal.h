#ifndef IANIMAL_H
#define IANIMAL_H

#include "oopcore.h"

#define TYPE_IAnimal { \
    void (*ShowInfo)(void*); \
};

CLASS(IAnimal)
INIT()

DESTRUCTOR(IAnimal);

#endif // IANIMAL_H
