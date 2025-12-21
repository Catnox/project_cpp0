#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

class Cure : public AMateria
{
public:
	// Canonical form
	Cure();
	Cure(Cure const & other);
	Cure & operator=(Cure const & other);
	virtual ~Cure();
	// Member functions
	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
};

#endif
