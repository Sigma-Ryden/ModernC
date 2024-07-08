#include "Cat.h"
#include "Dog.h"

int main() {
    {
        TCat* cat = CONSTRUCT(TCat, 40);
        IAnimal* animal = UPCAST(IAnimal, cat);
        animal->ShowInfo(animal);

        VIRTUAL_DESTRUCT(animal);
    }
    {
        TDog* dog = CONSTRUCT(TDog, "Jack", 200);

        TSmart* smart = UPCAST(TSmart, dog);
        TDog* other_dog = DOWNCAST(TSmart, TDog, smart);

        IAnimal* animal = UPCAST(IAnimal, other_dog);
        animal->ShowInfo(animal);

        DESTRUCT(TDog, dog);
    }
    return 0;
}
