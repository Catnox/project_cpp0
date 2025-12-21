#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

class Ice : public AMateria
{
public:
	// Canonical form
	Ice();
	Ice(Ice const & other);
	Ice & operator=(Ice const & other);
	virtual ~Ice();
	// Member functions
	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
};

#endif
