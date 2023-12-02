#ifndef OPPCORE_H
#define OPPCORE_H

#include <stdlib.h>
#include <stddef.h>

#define TO_PARENT(to, ptr) ((to*)(&ptr->__to_parent_##to))
#define TO_INTERFACE(to, ptr) ((to**)(&ptr->__to_interface_##to))
#define TO_CHILD(from, to, ptr) ((to*)((char*)ptr-(ptrdiff_t)offsetof(to, __to_child_##from)))

#define FUNCTION(type, name, ...) name(type *const self, ## __VA_ARGS__)

#define CONSTRUCTOR(type, ...) void* type##_Constructor(type *const self, ## __VA_ARGS__)
#define DESTRUCTOR(type, ...) void* type##_Destructor(type *const self, ## __VA_ARGS__)

#ifndef ALLOCATE
    #define ALLOCATE(type) (type*)calloc(1, sizeof(type))
#endif

#ifndef DEALLOCATE
    #define DEALLOCATE(ptr) free(ptr)
#endif

#define CONSTRUCT(type, ...) (type*)type##_Constructor(ALLOCATE(type), ## __VA_ARGS__)
#define CONSTRUCT_PARENT(type, ...) (type*)type##_Constructor(TO_PARENT(type, self), ## __VA_ARGS__)
#define CONSTRUCT_INTERFACE(interface, type) self->interface = &__vtable_##interface##_##type;

#define DESTRUCT(type, ptr) DEALLOCATE(type##_Destructor(ptr))
#define DESTRUCT_PARENT(type) type##_Destructor(TO_PARENT(self, type))
#define VIRTUAL_DESTRUCT(ptr) DEALLOCATE((*ptr)->__child_destructor((*ptr)->__child_implementation(ptr)))

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
        return TO_CHILD(interface, type, self);                                                         \
    }                                                                                                   \
    static const interface __vtable_##interface##_##type = {                                            \
        .__child_destructor = &__##type##_##interface##_destructor,                                     \
        .__child_implementation = &__##type##_##interface##_implementation,

#define OVERRIDE_FUNCTION(bind, function) .bind = &function,

#endif // OPPCORE_H
