#include <stdlib.h>
#include <stddef.h>

#define CONSTRUCTOR_IMPLEMENTATION(...) __VA_ARGS__)
#define CONSTRUCTOR(sname) sname* sname##_Constructor(sname *const CONSTRUCTOR_IMPLEMENTATION

#define DESTRUCTOR_IMPLEMENTATION(...) __VA_ARGS__)
#define DESTRUCTOR(sname) void sname##_Destructor(sname *const  DESTRUCTOR_IMPLEMENTATION

#define FUNCTION_IMPLEMENTATION(...) __VA_ARGS__)
#define FUNCTION(sname, fname) fname(sname *const FUNCTION_IMPLEMENTATION

#define CONSTRUCT_IMPLEMENTATION(...) __VA_ARGS__)
#define CONSTRUCT(sname) sname##_Constructor( (sname*)calloc(1, sizeof(sname)), CONSTRUCT_IMPLEMENTATION

#define DESTRUCT_IMPLEMENTATION(self) (self); free(self)
#define DESTRUCT(sname) sname##_Destructor DESTRUCT_IMPLEMENTATION

#define INIT(...) } __VA_ARGS__
#define EXTENDS(name) union { void* type_##name; struct STRUCT_##name }
#define STRUCT(name) typedef struct name name; struct name { EXTENDS(name);

#define IMPLEMENTS(name) union { void* type_I##name; struct INTERFACE_##name }
#define INTERFACE(name) typedef struct I##name I##name; struct I##name { IMPLEMENTS(name); }

#define CAST(pointer, to) ((to*)&pointer->type_##to)

// (to*)(-(ptrdiff_t)offsetof(to, type_##from)+(char*)pointer)
#define DOWNCAST(pointer, from, to) ((to*)(-(ptrdiff_t)offsetof(to, type_##from)+(char*)pointer))

// EXAMPLE:
#define INTERFACE_Human { \
    void (*PrintName)(void*); \
    int (*GetAge)(void*); \
};

INTERFACE(Human);

#define INTERFACE_Runable { \
    void (*Run)(IRunable*); \
};

INTERFACE(Runable);

#define STRUCT_Girl { \
    const char* Name; \
    int Age; \
};

#define STRUCT_Object { \
    int Id; \
};

STRUCT(Object)
INIT();

STRUCT(Girl)
    IMPLEMENTS(Runable);
    EXTENDS(Object);
    IMPLEMENTS(Human);
INIT();

#include <stdio.h>

void FUNCTION(void, Girl_PrintName)(pointer) {
    Girl* self = (Girl*)pointer;

    const char* format = "My name is %s, and I'm %i years old!\n";
    printf(format, self->Name, self->GetAge(self));
}

int FUNCTION(void, Girl_GetAge)(pointer) {
    Girl* self = (Girl*)pointer;
    return self->Age;
}

void FUNCTION(IRunable, Girl_Run)(runable) {
    Girl* self = DOWNCAST(runable, IRunable, Girl);
    printf("%s is running...\n", self->Name);
}

CONSTRUCTOR(Girl)(self, const char* name, int age) {
    self->Run = &Girl_Run;

    self->PrintName = &Girl_PrintName;
    self->GetAge = &Girl_GetAge;

    self->Name = name;
    self->Age = age;

    return self;
}

DESTRUCTOR(Girl)(self) {
    printf("Bye, %s!\n", self->Name);
}

int main() {
    Girl* girl = CONSTRUCT(Girl)("Sonya", 19);
    IHuman* human = CAST(girl, IHuman);
    human->PrintName(girl);

    IRunable* runable = CAST(girl, IRunable);
    runable->Run(runable);

    Girl* other = DOWNCAST(human, IHuman, Girl);
    DESTRUCT(Girl)(other);

    return 0;
}
