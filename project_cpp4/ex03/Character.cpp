#include "Character.hpp"

// Canonical form
Character::Character() : _name("default")
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	std::cout << "Character default constructor called" << std::endl;
}

Character::Character(Character const & other) : _name(other._name)
{
	for (int i = 0; i < 4; i++)
	{
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
	std::cout << "Character " << _name << " copy constructor called" << std::endl;
}

Character & Character::operator=(Character const & other)
{
	if (this != &other)
	{
		_name = other._name;
		for (int i = 0; i < 4; i++)
		{
			if (_inventory[i])
				delete _inventory[i];
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
			else
				_inventory[i] = NULL;
		}
	}
	return *this;
}

Character::~Character()
{
	std::cout << "Character " << _name << " destructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i])
			delete _inventory[i];
	}
}

// Custom constructor
Character::Character(std::string const & name) : _name(name)
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	std::cout << "Character " << _name << " constructor called" << std::endl;
}

// Getter
std::string const & Character::getName() const
{
	return this->_name;
}

// Member functions
void Character::equip(AMateria* m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; i++)
	{
		if (!_inventory[i])
		{
			_inventory[i] = m;
			std::cout << "Character " << _name << " equipped " << m->getType() << " in slot " << i << std::endl;
			return;
		}
	}
	std::cout << "Character " << _name << " inventory is full, cannot equip " << m->getType() << std::endl;
}

void Character::unequip(int idx)
{
	if (idx >= 0 && idx < 4)
	{
		if (_inventory[idx])
			std::cout << "Character " << _name << " unequipped slot " << idx << std::endl;
		else
			std::cout << "Character " << _name << " slot " << idx << " is already empty" << std::endl;
		_inventory[idx] = NULL;
	}
	else
		std::cout << "Character " << _name << " invalid unequip index: " << idx << std::endl;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx >= 0 && idx < 4 && _inventory[idx])
		_inventory[idx]->use(target);
	else if (idx < 0 || idx >= 4)
		std::cout << "Character " << _name << " invalid use index: " << idx << std::endl;
	else
		std::cout << "Character " << _name << " slot " << idx << " is empty, cannot use" << std::endl;
}
