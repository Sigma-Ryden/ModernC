#ifndef CAT_H
#define CAT_H

#include "IAnimal.h"

#define TYPE_TCat { \
    INHERITS(IAnimal) \
    int Speed; \
};

CLASS(TCat)
INIT()

CONSTRUCTOR(TCat, int speed);
DESTRUCTOR(TCat);

void FUNCTION(void, TCat_ShowInfo);
void FUNCTION(TCat, TCat_Voice);

#endif // CAT_H
