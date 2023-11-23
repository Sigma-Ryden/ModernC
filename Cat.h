#ifndef CAT_H
#define CAT_H

#include "IAnimal.h"

#define TYPE_TCat { \
    int Speed; \
};

CLASS(TCat)
    IMPLEMENTS(IAnimal)
INIT()

CONSTRUCTOR(TCat)(int speed);
DESTRUCTOR(TCat)();

void FUNCTION(void, TCat_ShowInfo)();

#endif // CAT_H
