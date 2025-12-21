#include "AMateria.hpp"
#include "ICharacter.hpp"

// Canonical form
AMateria::AMateria() : _type("default")
{
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(AMateria const & other) : _type(other._type)
{
	std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria &AMateria::operator=(AMateria const & other)
{
	(void)other;
	// Le type ne doit pas être copié
	return *this;
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor called" << std::endl;
}

// Custom constructor
AMateria::AMateria(std::string const & type) : _type(type)
{
	std::cout << "AMateria " << type << " constructor called" << std::endl;
}

// Getter
std::string const &AMateria::getType() const
{
	return this->_type;
}

// Member function
void AMateria::use(ICharacter& target)
{
	(void)target;
}
