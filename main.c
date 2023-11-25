#include "Cat.h"
#include "Dog.h"

int main() {
    {
        TCat* cat = CONSTRUCT(TCat)(40);
        IAnimal** animal = TO_INTERFACE(cat, IAnimal);
        (*animal)->ShowInfo(animal);
        VIRTUAL_DESTRUCT()(animal);
    }
    {
        TDog* dog = CONSTRUCT(TDog)("Volf", 200);
        IAnimal** animal = TO_INTERFACE(dog, IAnimal);
        (*animal)->ShowInfo(animal);
        VIRTUAL_DESTRUCT()(animal);
    }
    return 0;
}
