#include "Dog.hpp"

// Canonical form
Dog::Dog() : Animal()
{
    _type = "Dog";
    std::cout << "Dog Default constructed." << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
    std::cout << "Dog copy constructed." << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Dog::~Dog()
{
    std::cout << "Dog destructed." << std::endl;
}

// Member function
void Dog::makeSound() const
{
    std::cout << "Woof Woof!" << std::endl;
}
