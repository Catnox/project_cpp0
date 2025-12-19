#include "WrongAnimal.hpp"

// Canonical form
WrongAnimal::WrongAnimal() : _type("WrongAnimal")
{
    std::cout << "WrongAnimal Default constructed." << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) : _type(other._type)
{
    std::cout << "WrongAnimal copy constructed." << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other)
{
    if (this != &other)
        _type = other._type;
    return *this;
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal destructed." << std::endl;
}

// Getter
std::string WrongAnimal::getType() const
{
    return _type;
}

// Member function
void WrongAnimal::makeSound() const
{
    std::cout << "WrongAnimal sound!" << std::endl;
}
