#include "Cat.h"
#include "Dog.h"

int main() {
    {
        TCat* cat = NEW(TCat, 40);

        IAnimal* animal = UPCAST(IAnimal, cat);
        animal->ShowInfo(animal);

        DELETE(animal);
    }
    {
        TDog* dog = NEW(TDog, "Jack", 200);

        TSmart* smart = UPCAST(TSmart, dog);
        TDog* other_dog = DOWNCAST(TSmart, TDog, smart);

        IAnimal* animal = UPCAST(IAnimal, other_dog);
        animal->ShowInfo(animal);

        DELETE(dog);
    }
    {
        TCat place;
        TCat* cat = CONSTRUCT(TCat, &place, 32);

        place.Speed = 28;

        IAnimal* animal = UPCAST(IAnimal, cat);
        animal->ShowInfo(animal);

        DESTRUCT(cat);
    }
    return 0;
}
