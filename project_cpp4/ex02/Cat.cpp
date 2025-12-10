#include "Cat.hpp"

Cat::Cat() : Animal()
{
    _type = "Cat";
    _brain = new Brain();
    std::cout << "Cat Default constructed." << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
    _brain = new Brain(*other._brain);
    std::cout << "Cat copy constructed." << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    if (this != &other) {
        Animal::operator=(other);
        delete _brain;
        _brain = new Brain(*other._brain);
    }
    return *this;
}

Cat::~Cat()
{
    delete _brain;
    std::cout << "Cat destructed." << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}

Brain* Cat::getBrain() const
{
    return _brain;
}
