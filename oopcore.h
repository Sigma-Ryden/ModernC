#ifndef OPPCORE_H
#define OPPCORE_H

#include <stdlib.h>
#include <stddef.h>

#define CONSTRUCTOR_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define CONSTRUCTOR(sname) sname* sname##_Constructor(sname *const self CONSTRUCTOR_IMPLEMENTATION

#define DESTRUCTOR_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define DESTRUCTOR(sname) void sname##_Destructor(sname *const self DESTRUCTOR_IMPLEMENTATION

#define FUNCTION_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define FUNCTION(sname, fname) fname(sname *const self FUNCTION_IMPLEMENTATION

#define CONSTRUCT_IMPLEMENTATION(...) , ## __VA_ARGS__)
#define CONSTRUCT(sname) sname##_Constructor( (sname*)calloc(1, sizeof(sname)) CONSTRUCT_IMPLEMENTATION
#define CONSTRUCT_PARENT(psname) psname##_Constructor(CAST(self, psname) CONSTRUCT_IMPLEMENTATION

#define DESTRUCT_IMPLEMENTATION(self) (self); free(self)
#define DESTRUCT(sname) sname##_Destructor DESTRUCT_IMPLEMENTATION

#define DESTRUCT_PARENT(sname) sname##_Destructor(CAST(self, sname))

#define INIT(...) } __VA_ARGS__

#define EXTENDS(name) union { char TYPE_##name[sizeof(name)]; struct STRUCT_##name }
#define STRUCT(name) typedef struct name name; struct name { union { char TYPE_##name[1]; struct STRUCT_##name };

#define IMPLEMENTS(name) union { char TYPE_I##name[sizeof(I##name)]; struct INTERFACE_##name }
#define INTERFACE(name) typedef struct I##name I##name; struct I##name { union { char TYPE_I##name[1]; struct INTERFACE_##name };

#define CAST(pointer, to) ((to*)&pointer->TYPE_##to)

// (to*)((char*)pointer-(ptrdiff_t)offsetof(to, type_##from))
#define DOWNCAST(pointer, from, to) ((to*)((char*)pointer-(ptrdiff_t)offsetof(to, TYPE_##from)))

#endif // OPPCORE_H
