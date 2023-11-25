#ifndef OPPCORE_H
#define OPPCORE_H

#include <stdlib.h>
#include <stddef.h>

#define TO_PARENT(pointer, to) ((to*)(&(pointer)->__to_parent_##to))
#define TO_INTERFACE(pointer, to) ((to**)(&(pointer)->__to_interface_##to))
#define TO_CHILD(pointer, from, to) ((to*)((char*)(pointer)-(ptrdiff_t)offsetof(to, __to_child_##from)))

#define FUNCTION_IMPLEMENTATION(...) , ## __VA_ARGS__)

#define FUNCTION(type, name) name(type *const self FUNCTION_IMPLEMENTATION

#define CONSTRUCTOR(type) void* type##_Constructor(type *const self FUNCTION_IMPLEMENTATION
#define DESTRUCTOR(type) void* type##_Destructor(type *const self FUNCTION_IMPLEMENTATION

#define CONSTRUCT(type) (type*)type##_Constructor((type*)calloc(1, sizeof(type)) FUNCTION_IMPLEMENTATION
#define CONSTRUCT_PARENT(type) (type*)type##_Constructor(TO_PARENT(self, type) FUNCTION_IMPLEMENTATION

#define DESTRUCT_IMPLEMENTATION(pointer) pointer))
#define DESTRUCT(type) free(type##_Destructor(DESTRUCT_IMPLEMENTATION

#define DESTRUCT_PARENT_IMPLEMENTATION()
#define DESTRUCT_PARENT(type) type##_Destructor(TO_PARENT(self, type)) DESTRUCT_PARENT_IMPLEMENTATION

#define VIRTUAL_DESTRUCT_IMPLEMENTATION(pointer)                                                        \
    (*(pointer))->__child_destructor((*(pointer))->__child_implementation((pointer)))

#define VIRTUAL_DESTRUCT(type) VIRTUAL_DESTRUCT_IMPLEMENTATION

#define IMPLEMENTS(type)                                                                                \
    union {                                                                                             \
        char __to_interface_##type[sizeof(type)];                                                       \
        char __to_child_##type[sizeof(type)];                                                           \
        struct {                                                                                        \
            const type* type;                                                                           \
        };                                                                                              \
    };

#define EXTENDS(type)                                                                                   \
    union {                                                                                             \
        char __to_parent_##type[sizeof(type)];                                                          \
        char __to_child_##type[sizeof(type)];                                                           \
        struct TYPE_##type                                                                              \
    };

#define INTERFACE(type)                                                                                 \
    typedef struct type type;                                                                           \
    struct type {                                                                                       \
        union {                                                                                         \
            char __to_interface_##type[1];                                                              \
            struct TYPE_##type                                                                          \
        };                                                                                              \
        void* (*__child_destructor)(void*);                                                             \
        void* (*__child_implementation)(void*);

#define CLASS(type)                                                                                     \
    typedef struct type type;                                                                           \
    struct type {                                                                                       \
        union {                                                                                         \
            char __to_parent_##type[1];                                                                 \
            struct TYPE_##type                                                                          \
        };

#define INIT(...) } __VA_ARGS__;

#define VIRTUAL_TABLE(interface, type)                                                                  \
    static void* __##type##_##interface##_destructor(void* self) {                                      \
        return type##_Destructor((type*)self);                                                          \
    }                                                                                                   \
    static void* __##type##_##interface##_implementation(void* self) {                                  \
        return TO_CHILD(self, interface, type);                                                         \
    }                                                                                                   \
    static const interface __vtable_##interface##_##type = {                                            \
        .__child_destructor = &__##type##_##interface##_destructor,                                     \
        .__child_implementation = &__##type##_##interface##_implementation,

#define OVERRIDE_FUNCTION(bind, function) .bind = &function,

#define CONSTRUCT_INTERFACE_IMPLEMENTATION()
#define CONSTRUCT_INTERFACE(interface, type)                                                            \
    self->interface = &__vtable_##interface##_##type; CONSTRUCT_INTERFACE_IMPLEMENTATION

#endif // OPPCORE_H
