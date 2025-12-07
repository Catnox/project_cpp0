#include "ClapTrap.hpp"

int main()
{
	ClapTrap clap("CL4P-TP");

	clap.attack("Bandit");
	clap.takeDamage(5);
	clap.beRepaired(3);
	clap.takeDamage(10);
	clap.attack("Bandit");

	return 0;
}