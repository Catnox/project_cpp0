#include "ScavTrap.hpp"
#include <iostream>

int main()
{
    ScavTrap scav("SC4V-TP");
    scav.attack("Bandit");
    scav.takeDamage(20);
    scav.beRepaired(10);
    scav.guardGate();
    scav.takeDamage(100);
    scav.attack("Bandit");
    return 0;
}
