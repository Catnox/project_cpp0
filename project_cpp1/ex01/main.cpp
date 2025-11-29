#include "Zombie.hpp"

int main()
{
	Zombie z;
	Zombie* horde = z.zombieHorde(5, "HordeZombie");
	for (int i = 0; i < 5; i++)
	{
		horde[i].announce();
	}
	delete[] horde;
	return 0;
}