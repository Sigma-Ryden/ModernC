#ifndef IANIMAL_H
#define IANIMAL_H

#include <ModernC/Core.h>

#define TYPE_IAnimal { \
    void (*ShowInfo)(void*); \
};

CLASS(IAnimal)
INIT()

DESTRUCTOR(IAnimal);

#endif // IANIMAL_H
