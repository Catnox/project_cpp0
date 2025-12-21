#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character : public ICharacter
{
private:
	std::string _name;
	AMateria*	_inventory[4];

public:
	// Canonical form
	Character();
	Character(Character const & other);
	Character & operator=(Character const & other);
	virtual ~Character();
	// Custom constructor
	Character(std::string const & name);
	// Getter
	virtual std::string const & getName() const;
	// Member functions
	virtual void equip(AMateria* m);
	virtual void unequip(int idx);
	virtual void use(int idx, ICharacter& target);
};

#endif
