#ifndef GIRL_H
#define GIRL_H

#include "IHuman.h"
#include "IRunable.h"

#define STRUCT_Ticket { \
    int Id; \
};

STRUCT(Ticket)
INIT();

CONSTRUCTOR(Ticket)();
DESTRUCTOR(Ticket)();

#define STRUCT_Girl { \
    const char* Name; \
    int Age; \
};

STRUCT(Girl)
    IMPLEMENTS(Runable);
    EXTENDS(Ticket);
    IMPLEMENTS(Human);
INIT();

CONSTRUCTOR(Girl)(const char* name, int age);
DESTRUCTOR(Girl)();

void FUNCTION(void, Girl_PrintName)();
int FUNCTION(void, Girl_GetAge)();
void FUNCTION(IRunable, Girl_Run)();

#endif // GIRL_H
