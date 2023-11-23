#include "Cat.h"

#include <stdio.h>

VIRTUAL_TABLE(IAnimal, TCat)
    BIND_FUNCTION(ShowInfo, TCat_ShowInfo)
INIT()

CONSTRUCTOR(TCat)(int speed) {
    BIND_VIRTUAL_TABLE(self, IAnimal, TCat);

    self->Speed = speed;

    printf("Create Cat\n");
    return self;
}

DESTRUCTOR(TCat)() {
    printf("Destoy Cat\n");
    return self;
}

void FUNCTION(void, TCat_ShowInfo)() {
    TCat* cat = TO_CHILD(self, IAnimal, TCat);
    printf("Cat speed: %i\n", cat->Speed);
}
