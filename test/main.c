#include "Cat.h"
#include "Dog.h"

int main() {
    {
        TCat* cat = NEW(TCat, 40);

        IAnimal* animal = UPCAST(IAnimal, cat);
        animal->ShowInfo(animal);

        TCat_Voice(cat);

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

        IAnimal* animal = UPCAST(IAnimal, cat);
        animal->ShowInfo(animal);

        place.Speed = 28;
        cat->ShowInfo(animal);

        DESTRUCT(cat);
    }
    return 0;
}
