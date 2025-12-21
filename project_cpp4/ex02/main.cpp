#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    // AAnimal* meta = new AAnimal(); // ERROR: AAnimal is abstract, cannot instantiate

    std::cout << "=== Test de base ==="<< std::endl;
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound();
    j->makeSound();
    delete j;
    delete i;

    std::cout << std::endl << "=== Test tableau d'animaux ===" << std::endl;
    const int size = 4;
    AAnimal* animals[size];
    for (int idx = 0; idx < size / 2; idx++)
        animals[idx] = new Dog();
    for (int idx = size / 2; idx < size; idx++)
        animals[idx] = new Cat();
    for (int idx = 0; idx < size; idx++)
        animals[idx]->makeSound();
    for (int idx = 0; idx < size; idx++)
        delete animals[idx];

    std::cout << std::endl << "=== Test deep copy Dog ===" << std::endl;
    Dog dog1;
    dog1.getBrain()->setIdea(0, "I love bones");
    Dog dog2(dog1);
    std::cout << "dog1 idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;
    dog2.getBrain()->setIdea(0, "I love running");
    std::cout << "After modifying dog2:" << std::endl;
    std::cout << "dog1 idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;

    std::cout << std::endl << "=== Test deep copy Cat ===" << std::endl;
    Cat cat1;
    cat1.getBrain()->setIdea(0, "I love fish");
    Cat cat2(cat1);
    std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
    std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;
    cat2.getBrain()->setIdea(0, "I love naps");
    std::cout << "After modifying cat2:" << std::endl;
    std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
    std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

    return 0;
}