#ifndef IRUNABLE_H
#define IRUNABLE_H

#include "oopcore.h"

#define INTERFACE_Runable { \
    void (*Run)(IRunable*); \
};

INTERFACE(Runable)
INIT();

#endif // IRUNABLE_H
