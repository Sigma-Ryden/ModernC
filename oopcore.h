#ifndef OPPCORE_H
#define OPPCORE_H

#include <stdlib.h>
#include <stddef.h>

#define UPCAST(to, ptr) ((to*)(&(ptr)->__to_parent_##to))
#define DOWNCAST(from, to, ptr) ((to*)((char*)(ptr)-(ptrdiff_t)offsetof(to, __to_child_##from)))

#define FUNCTION(type, name, ...) name(type *const self, ## __VA_ARGS__)

#define CONSTRUCTOR(type, ...) void* type##_Constructor(type *const self, ## __VA_ARGS__)
#define DESTRUCTOR(type, ...) void* type##_Destructor(type *const self, ## __VA_ARGS__)

#define CONSTRUCT(type, place, ...)                                                                     \
    (__oopcore=place, ((type*)__oopcore)->__destructor=&type##_Destructor,                              \
     (type*)type##_Constructor((type*)__oopcore, ## __VA_ARGS__))

#define DESTRUCT(ptr) ((ptr)->__destructor(ptr), ptr->__destructor=NULL, ptr)

#define CONSTRUCT_PARENT(type, ...) (type*)type##_Constructor(UPCAST(type, self), ## __VA_ARGS__)
#define DESTRUCT_PARENT(type) type##_Destructor(UPCAST(type, self))

#define NEW(type, ...) CONSTRUCT(type, ((type*)calloc(1, sizeof(type))), ## __VA_ARGS__)
#define DELETE(ptr) free(DESTRUCT(ptr))

#define INHERITS(type)                                                                                  \
    union {                                                                                             \
        char __to_parent_##type[sizeof(type)]; char __to_child_##type[sizeof(type)]; struct TYPE_##type \
    };

#define CLASS(type)                                                                                     \
    typedef struct type type;                                                                           \
    struct type {                                                                                       \
        union { char __to_parent_##type[1]; struct TYPE_##type };                                       \
        void* (*__destructor)(type *const);

#define INIT(...) } __VA_ARGS__;

#define VIRTUAL_TABLE(interface, type)                                                                  \
    extern const interface __vtable_##interface##_##type;                                               \
    static void* interface##_Constructor(interface *const self) {                                       \
        *self = __vtable_##interface##_##type; return self;                                             \
    }                                                                                                   \
    static void* __##type##_##interface##_Destructor(interface *const self) {                           \
        type* child = DOWNCAST(interface, type, self); return child->__destructor(child);               \
    }                                                                                                   \
    const interface __vtable_##interface##_##type = {                                                   \
        .__destructor = &__##type##_##interface##_Destructor,                                           \

#define OVERRIDE_FUNCTION(bind, function) .bind = &function,

extern void* __oopcore;

#endif // OPPCORE_H
