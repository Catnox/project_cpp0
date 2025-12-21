#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>
# include <iostream>

class ICharacter;

class AMateria
{
protected:
	std::string _type;

public:
	// Canonical form
	AMateria();
	AMateria(AMateria const & other);
	AMateria &operator=(AMateria const & other);
	virtual ~AMateria();
	// Custom constructor
	AMateria(std::string const & type);
	// Getter
	std::string const &getType() const;
	// Pure virtual member functions
	virtual AMateria* clone() const = 0;
	// Member function
	virtual void use(ICharacter& target);
};

#endif