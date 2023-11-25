#include "Dog.h"

#include <stdio.h>

CONSTRUCTOR(TSmart)() {
    return self;
}

DESTRUCTOR(TSmart)() {
    return self;
}

VIRTUAL_TABLE(IAnimal, TDog)
    OVERRIDE_FUNCTION(ShowInfo, TDog_ShowInfo)
INIT()

CONSTRUCTOR(TDog)(const char* name, int force) {
    CONSTRUCT_PARENT(TSmart)();
    CONSTRUCT_INTERFACE(IAnimal, TDog)();

    TO_PARENT(self, TSmart)->Name = name;
    self->Force = force;

    printf("Create Dog\n");
    return self;
}

DESTRUCTOR(TDog)() {
    printf("Destoy Dog\n");
    return self;
}

void FUNCTION(void, TDog_ShowInfo)() {
    TDog* dog = TO_CHILD(self, IAnimal, TDog);
    printf("Dog name: %s, force: %i\n", dog->Name, dog->Force);
}
