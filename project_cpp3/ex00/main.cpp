#include "ClapTrap.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Test 1: Basic operations ===" << std::endl;
	ClapTrap clap("clappy");
	clap.attack("ennemy");
	clap.takeDamage(5);
	clap.beRepaired(3);
	clap.takeDamage(10);
	clap.attack("ennemy");

	std::cout << "\n=== Test 2: Energy exhaustion ===" << std::endl;
	ClapTrap tired("Tired");
	for (int i = 0; i < 12; ++i) {
		tired.attack("ennemy");
	}

	std::cout << "\n=== Test 3: HP reaches zero ===" << std::endl;
	ClapTrap fragile("Fragile");
	fragile.takeDamage(10);
	fragile.attack("enemy");
	fragile.beRepaired(5);

	std::cout << "\n=== Test 4: Repair with no energy ===" << std::endl;
	ClapTrap noEnergy("NoEnergy");
	for (int i = 0; i < 10; ++i) {
		noEnergy.attack("dummy");
	}
	noEnergy.beRepaired(5);

	return (0);
}