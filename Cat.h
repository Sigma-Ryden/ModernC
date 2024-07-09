#ifndef CAT_H
#define CAT_H

#include "IAnimal.h"

#define TYPE_TCat { \
    int Speed; \
};

CLASS(TCat)
    INHERITS(IAnimal)
INIT()

CONSTRUCTOR(TCat, int speed);
DESTRUCTOR(TCat);

void FUNCTION(void, TCat_ShowInfo);
void FUNCTION(TCat, TCat_Voice);

#endif // CAT_H
