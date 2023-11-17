#include "UberGirl.h"

CONSTRUCTOR(UberGirl)(const char* name, int age) {
    CONSTRUCT_PARENT(Girl)(name, age);
    return self;
}

DESTRUCTOR(UberGirl)() {
    DESTRUCT_PARENT(Girl);
}
