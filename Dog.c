#include "Dog.h"

#include <stdio.h>

CONSTRUCTOR(TSmart) {
    return self;
}

DESTRUCTOR(TSmart) {
    return self;
}

VIRTUAL_TABLE(IAnimal, TDog)
    OVERRIDE_FUNCTION(ShowInfo, TDog_ShowInfo)
INIT()

CONSTRUCTOR(TDog, const char* name, int force) {
    CONSTRUCT_PARENT(TSmart);
    CONSTRUCT_PARENT(IAnimal);

    UPCAST(TSmart, self)->Name = name;
    self->Force = force;

    printf("Create Dog\n");
    return self;
}

DESTRUCTOR(TDog) {
    printf("Destoy Dog\n");

    DESTRUCT_PARENT(IAnimal);
    DESTRUCT_PARENT(TSmart);
    return self;
}

void FUNCTION(void, TDog_ShowInfo) {
    TDog* dog = DOWNCAST(IAnimal, TDog, self);
    printf("Dog name: %s, force: %i\n", dog->Name, dog->Force);
}
