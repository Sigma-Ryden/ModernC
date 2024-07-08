#include "Cat.h"
#include "Dog.h"

int main() {
    {
        TCat* cat = CONSTRUCT(TCat, 40);
        IAnimal* animal = TO_INTERFACE(IAnimal, cat);
        animal->ShowInfo(animal);

        VIRTUAL_DESTRUCT(animal);
    }
    {
        TDog* dog = CONSTRUCT(TDog, "Jack", 200);

        TSmart* smart = TO_PARENT(TSmart, dog);
        TDog* other_dog = TO_CHILD(TSmart, TDog, smart);

        IAnimal* animal = TO_INTERFACE(IAnimal, other_dog);
        animal->ShowInfo(animal);

        DESTRUCT(TDog, dog);
    }
    return 0;
}
