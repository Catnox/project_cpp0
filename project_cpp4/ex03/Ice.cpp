#include "Ice.hpp"
#include "ICharacter.hpp"

// Canonical form
Ice::Ice() : AMateria("ice")
{
	std::cout << "Ice default constructor called" << std::endl;
}

Ice::Ice(Ice const & other) : AMateria(other)
{
	std::cout << "Ice copy constructor called" << std::endl;
}

Ice & Ice::operator=(Ice const & other)
{
	if (this != &other)
		AMateria::operator=(other);
	return *this;
}

Ice::~Ice()
{
	std::cout << "Ice destructor called" << std::endl;
}

// Member functions
AMateria* Ice::clone() const
{
	return new Ice(*this);
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
