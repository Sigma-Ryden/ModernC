#ifndef UBER_GIRL_H
#define UBER_GIRL_H

#include "Girl.h"

#define STRUCT_UberGirl { \
};

STRUCT(UberGirl)
    EXTENDS(Girl);
INIT();

CONSTRUCTOR(UberGirl)(const char* name, int age);
DESTRUCTOR(UberGirl)();

#endif // UBER_GIRL_H
