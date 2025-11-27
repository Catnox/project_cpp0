#include "Zombie.hpp"

int main()
{
	Zombie* zombie1 = Zombie::newZombie("Zombie1");
	zombie1->announce();
	Zombie::randomChump("Zombie2");
	delete zombie1;
	return 0;
}