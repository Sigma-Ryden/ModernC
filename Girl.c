#include "Girl.h"

#include <stdio.h>

CONSTRUCTOR(Ticket)() {
    return self;
}

DESTRUCTOR(Ticket)() {
}

CONSTRUCTOR(Girl)(const char* name, int age) {
    CONSTRUCT_PARENT(Ticket)();

    self->Run = &Girl_Run;

    self->PrintName = &Girl_PrintName;
    self->GetAge = &Girl_GetAge;

    self->Name = name;
    self->Age = age;

    return self;
}

DESTRUCTOR(Girl)() {
    printf("Bye, %s!\n", self->Name);
}

void FUNCTION(void, Girl_PrintName)() {
    Girl* girl = (Girl*)self;

    const char* format = "My name is %s, and I'm %i years old!\n";
    printf(format, girl->Name, girl->GetAge(self));
}

int FUNCTION(void, Girl_GetAge)() {
    Girl* girl = (Girl*)self;
    return girl->Age;
}

void FUNCTION(IRunable, Girl_Run)() {
    Girl* girl = DOWNCAST(self, IRunable, Girl);
    printf("%s is running...\n", girl->Name);
}

