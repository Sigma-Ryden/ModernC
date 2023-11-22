#include "UberGirl.h"

#include <stdio.h>

void TestOOPCore() {
    Girl* girl = CONSTRUCT(Girl)("Sonya", 19);

    IHuman* human = CAST(girl, IHuman);
    human->PrintName(girl);

    IRunable* runable = CAST(girl, IRunable);
    runable->Run(runable);

    {
        UberGirl* ubergirl = CONSTRUCT(UberGirl)("Ayesha", girl->GetAge(girl)+2);

        Girl* parent = CAST(ubergirl, Girl);
        parent->PrintName(parent);

        DESTRUCT(UberGirl)(ubergirl);
    }

    Girl* other = DOWNCAST(human, IHuman, Girl);
    DESTRUCT(Girl)(other);
}

#define __IMPLEMENTS(type) \
    union { \
        char __INTERFACE_##type[sizeof(type)]; \
        struct { \
            const type* type; \
        }; \
    }

#define __EXTENDS(type) \
    union { \
        char __CLASS_##type[sizeof(type)]; \
        struct CLASS_##type \
    }

#define __CLASS(type) \
    typedef struct type type; \
    struct type { \
        union { \
            char __CLASS_##type[1]; \
            struct CLASS_##type \
        };

#define __INTERFACE(type) \
    typedef struct type type; \
    struct type { \
        union { \
            char __INTERFACE_##type[1]; \
            struct CLASS_##type \
        };

#define __INIT(...) } __VA_ARGS__

#define __VIRTUAL_TABLE(interface, type) \
    const interface interface##_##type = { \

#define __VIRTUAL_FUNCTION(vfunction, function) \
    .vfunction = &function,


#define __CAST(pointer, to) (to*)(&pointer->__CLASS_##to)
#define __IMPLEMENTATION_INTERFACE(pointer, to) *(to**)(&pointer->__INTERFACE_##to)
#define __DOWNCAST(pointer, from, to) (to*)((char*)pointer-(ptrdiff_t)offsetof(to, __CLASS_##from));
#define __INTERFACE_IMPLEMENTATION(pointer, from, to) (to*)((char*)(&pointer)-(ptrdiff_t)offsetof(to, __INTERFACE_##from));



#define CLASS_Interface { \
    void(*DoSomething)(void*); \
};

#define CLASS_InterfaceCore { \
    void*(*Meta)(); \
};

__CLASS(InterfaceCore)
__INIT();

__INTERFACE(Interface)
    __EXTENDS(InterfaceCore);
__INIT();

#define CLASS_Implementation { \
    void* SomeData; \
};

#define CLASS_Object { \
    int ID; \
};

__CLASS(Object)
__INIT();

__CLASS(Implementation)
    __EXTENDS(Object);
    __IMPLEMENTS(Interface);
__INIT();

void Implementation_DoSomething(void* self) {
}

void* Implementation_Meta() {
    return NULL;
}

__VIRTUAL_TABLE(Interface, Implementation)
    __VIRTUAL_FUNCTION(DoSomething, Implementation_DoSomething)
    __VIRTUAL_FUNCTION(Meta, Implementation_Meta)
__INIT();

void TestDownCast(Interface* interface) {
    Implementation* impl = __INTERFACE_IMPLEMENTATION(interface, Interface, Implementation);
    impl->Interface->DoSomething(impl);
    impl->Interface->Meta();
}

void TestInterface() {
    Implementation* impl = (Implementation*)calloc(1, sizeof(Implementation));
    impl->Interface = &Interface_Implementation;
    impl->Interface->DoSomething(impl);
    impl->ID = 321;

    Object* object = __CAST(impl, Object);
    object->ID = 123;

    Implementation* other_impl = __DOWNCAST(object, Object, Implementation);
    other_impl->Interface->DoSomething(other_impl);

    Interface* interface = __IMPLEMENTATION_INTERFACE(impl, Interface);
    interface->DoSomething(impl);

    TestDownCast(interface);
}

int main() {
    TestInterface();
    TestOOPCore();

    return 0;
}
