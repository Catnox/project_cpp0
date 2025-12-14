#include "Dog.hpp"

// Canonical form
Dog::Dog() : Animal()
{
    _type = "Dog";
    _brain = new Brain();
    std::cout << "Dog Default constructed." << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
    _brain = new Brain(*other._brain);
    std::cout << "Dog copy constructed." << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other) {
        Animal::operator=(other);
        delete _brain;
        _brain = new Brain(*other._brain);
    }
    return *this;
}

Dog::~Dog()
{
    delete _brain;
    std::cout << "Dog destructed." << std::endl;
}

// Member function
void Dog::makeSound() const
{
    std::cout << "Woof Woof!" << std::endl;
}

Brain* Dog::getBrain() const
{
    return _brain;
}
