#include "Cat.h"

#include <stdio.h>

VIRTUAL_TABLE(IAnimal, TCat)
    OVERRIDE_FUNCTION(ShowInfo, TCat_ShowInfo)
INIT()

CONSTRUCTOR(TCat, int speed) {
    CONSTRUCT_PARENT(IAnimal);

    self->Speed = speed;

    printf("Create Cat\n");
    return self;
}

DESTRUCTOR(TCat) {
    printf("Destoy Cat\n");

    DESTRUCT_PARENT(IAnimal);
    return self;
}

void FUNCTION(void, TCat_ShowInfo) {
    TCat* cat = DOWNCAST(IAnimal, TCat, self);
    printf("Cat speed: %i\n", cat->Speed);
}

void FUNCTION(TCat, TCat_Voice) {
    printf("Cat say muuuue\n");
}
