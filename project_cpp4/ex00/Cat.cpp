#include "Cat.hpp"

// Canonical form
Cat::Cat() : Animal()
{
    _type = "Cat";
    std::cout << "Cat Default constructed." << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
    std::cout << "Cat copy constructed." << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Cat::~Cat()
{
    std::cout << "Cat destructed." << std::endl;
}

// Member function
void Cat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}
