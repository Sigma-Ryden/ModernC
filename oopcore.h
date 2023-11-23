#ifndef OPPCORE_H
#define OPPCORE_H

#include <stdlib.h>
#include <stddef.h>

#define CONSTRUCTOR_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define CONSTRUCTOR(sname) void* sname##_Constructor(sname *const self CONSTRUCTOR_IMPLEMENTATION

#define DESTRUCTOR_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define DESTRUCTOR(sname) void* sname##_Destructor(sname *const self DESTRUCTOR_IMPLEMENTATION

#define FUNCTION_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define FUNCTION(sname, fname) fname(sname *const self FUNCTION_IMPLEMENTATION

#define CONSTRUCT_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define CONSTRUCT(sname) (sname*)sname##_Constructor( (sname*)calloc(1, sizeof(sname)) CONSTRUCT_IMPLEMENTATION
#define CONSTRUCT_PARENT(psname) (psname*)psname##_Constructor(TO_PARENT(self, psname) CONSTRUCT_IMPLEMENTATION

#define DESTRUCT_IMPLEMENTATION(self, ...) self, ## __VA_ARGS__))
#define DESTRUCT(sname) free( sname##_Destructor( DESTRUCT_IMPLEMENTATION

#define DESTRUCT_PARENT_IMPLEMENTATION(self, ...) , ## __VA_ARGS__);
#define DESTRUCT_PARENT(sname) sname##_Destructor(TO_PARENT(self, sname) DESTRUCT_PARENT_IMPLEMENTATION

#define IMPLEMENTS(type) union { char __to_interface_##type[sizeof(type)]; char __to_child_##type[sizeof(type)]; struct { type* type; }; };
#define EXTENDS(type) union { char __to_parent_##type[sizeof(type)]; char __to_child_##type[sizeof(type)]; struct TYPE_##type };

#define INTERFACE(type) typedef struct type type; struct type { union { char __to_interface_##type[1]; struct TYPE_##type };
#define CLASS(type) typedef struct type type; struct type { union { char __to_parent_##type[1]; struct TYPE_##type };

#define INIT(...) } __VA_ARGS__;

#define VIRTUAL_TABLE(interface, type) static interface interface##_##type = {
#define BIND_FUNCTION(bind, function) .bind = &function,
#define BIND_VIRTUAL_TABLE(pointer, interface, type) (pointer)->interface = &interface##_##type;

#define TO_PARENT(pointer, to) ((to*)(&(pointer)->__to_parent_##to))
#define TO_INTERFACE(pointer, to) ((to**)(&(pointer)->__to_interface_##to))
#define TO_CHILD(pointer, from, to) ((to*)((char*)(pointer)-(ptrdiff_t)offsetof(to, __to_child_##from)))

#endif // OPPCORE_H
