#ifndef DOG_H
#define DOG_H

#include "IAnimal.h"

#define TYPE_TSmart { \
    const char* Name; \
};

CLASS(TSmart)
INIT()

CONSTRUCTOR(TSmart);
DESTRUCTOR(TSmart);

#define TYPE_TDog { \
    int Force; \
};

CLASS(TDog)
    INHERITS(IAnimal)
    INHERITS(TSmart)
INIT()

CONSTRUCTOR(TDog, const char* name, int force);
DESTRUCTOR(TDog);

void FUNCTION(void, TDog_ShowInfo);

#endif // DOG_H
