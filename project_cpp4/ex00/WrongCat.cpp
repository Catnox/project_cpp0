#include "WrongCat.hpp"

// Canonical form
WrongCat::WrongCat() : WrongAnimal()
{
    _type = "WrongCat";
    std::cout << "WrongCat Default constructed." << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other)
{
    std::cout << "WrongCat copy constructed." << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
    if (this != &other) {
        WrongAnimal::operator=(other);
    }
    return *this;
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructed." << std::endl;
}

// Member function
void WrongCat::makeSound() const
{
    std::cout << "WrongCat Meow!" << std::endl;
}
