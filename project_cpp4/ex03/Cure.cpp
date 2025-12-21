#include "Cure.hpp"
#include "ICharacter.hpp"

// Canonical form
Cure::Cure() : AMateria("cure")
{
	std::cout << "Cure default constructor called" << std::endl;
}

Cure::Cure(Cure const & other) : AMateria(other)
{
	std::cout << "Cure copy constructor called" << std::endl;
}

Cure & Cure::operator=(Cure const & other)
{
	if (this != &other)
		AMateria::operator=(other);
	return *this;
}

Cure::~Cure()
{
	std::cout << "Cure destructor called" << std::endl;
}

// Member functions
AMateria* Cure::clone() const
{
	return new Cure(*this);
}

void Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
