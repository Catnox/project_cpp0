#include "AAnimal.hpp"

AAnimal::AAnimal() : _type("Animal")
{
    std::cout << "Animal Default constructed." << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : _type(other._type)
{
    std::cout << "Animal copy constructed." << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other)
{
    if (this != &other) {
        _type = other._type;
    }
    return *this;
}

AAnimal::~AAnimal()
{
    std::cout << "Animal destructed." << std::endl;
}

std::string AAnimal::getType() const
{
    return _type;
}
