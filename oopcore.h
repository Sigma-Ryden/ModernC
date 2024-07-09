#ifndef OPPCORE_H
#define OPPCORE_H

#include <stdlib.h>
#include <stddef.h>

#define UPCAST(to, ptr) ((to*)(&(ptr)->__to_parent_##to))
#define DOWNCAST(from, to, ptr) ((to*)((char*)(ptr)-(ptrdiff_t)offsetof(to, __to_child_##from)))

#define FUNCTION(type, name, ...) name(type *const self, ## __VA_ARGS__)

#define CONSTRUCTOR(type, ...) void* type##_Constructor(type *const self, ## __VA_ARGS__)
#define DESTRUCTOR(type, ...) void* type##_Destructor(type *const self, ## __VA_ARGS__)

#define CONSTRUCT(type, ...) (type*)type##_Constructor((type*)calloc(1, sizeof(type)), ## __VA_ARGS__)
#define DESTRUCT(ptr) free(ptr->__destructor(ptr))

#define CONSTRUCT_SELF(type) self->__destructor = &type##_Destructor;
#define CONSTRUCT_PARENT(type, ...) (type*)type##_Constructor(UPCAST(type, self), ## __VA_ARGS__)
#define DESTRUCT_PARENT(type) type##_Destructor(UPCAST(type, self))

#define INHERITS(type)                                                                                  \
    union {                                                                                             \
        char __to_parent_##type[sizeof(type)];                                                          \
        char __to_child_##type[sizeof(type)];                                                           \
        struct TYPE_##type                                                                              \
    };

#define INTERFACE(type)                                                                                 \
    typedef struct type type;                                                                           \
    struct type {                                                                                       \
        union {                                                                                         \
            char __to_parent_##type[1];                                                                 \
            struct TYPE_##type                                                                          \
        };                                                                                              \
        void* (*__destructor)(void *const);

#define CLASS(type)                                                                                     \
    typedef struct type type;                                                                           \
    struct type {                                                                                       \
        union {                                                                                         \
            char __to_parent_##type[1];                                                                 \
            struct TYPE_##type                                                                          \
        };                                                                                              \
        void* (*__destructor)(type *const);

#define INIT(...) } __VA_ARGS__;

#define VIRTUAL_TABLE(interface, type)                                                                  \
    extern const interface __vtable_##interface##_##type;                                               \
    static void* interface##_Constructor(void *const self) {                                            \
        *(interface*)self = __vtable_##interface##_##type;                                              \
        return self;                                                                                    \
    }                                                                                                   \
    static void* __##type##_##interface##_Destructor(void *const self) {                                \
        type* child = DOWNCAST(interface, type, self);                                                  \
        return child->__destructor(child);                                                              \
    }                                                                                                   \
    const interface __vtable_##interface##_##type = {                                                   \
        .__destructor = &__##type##_##interface##_Destructor,                                           \

#define OVERRIDE_FUNCTION(bind, function) .bind = &function,

#endif // OPPCORE_H
