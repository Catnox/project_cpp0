#include "Weapon.hpp"

Weapon::Weapon( std::string weaponType ) : type(weaponType) {}

Weapon::~Weapon() {}

const std::string& Weapon::getType( void ) const
{
	return this->type;
}

void Weapon::setType( std::string weaponType )
{
	this->type = weaponType;
}