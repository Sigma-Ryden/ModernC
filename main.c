#include "Cat.h"
#include "Dog.h"

int main() {
    TCat* cat = CONSTRUCT(TCat)(40);
    TDog* dog = CONSTRUCT(TDog)("Volf", 200);

    IAnimal** animals[] = {
        TO_INTERFACE(cat, IAnimal),
        TO_INTERFACE(dog, IAnimal)
    };

    for(int i = 0; i<2; ++i) {
        IAnimal** animal = animals[i];
        (*animal)->ShowInfo(animal);
    }

    TCat* samecat = TO_CHILD(animals[0], IAnimal, TCat);
    DESTRUCT(TCat)(samecat);

    DESTRUCT(TDog)(dog);

    return 0;
}
