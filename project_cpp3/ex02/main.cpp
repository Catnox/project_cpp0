#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main() {
    FragTrap frag("FR4G-TP");
    frag.attack("Bandit");
    frag.takeDamage(30);
    frag.beRepaired(20);
    frag.highFivesGuys();
    frag.takeDamage(100);
    frag.attack("Bandit");

    std::cout << "---" << std::endl;

    ScavTrap scav("SC4V-TP");
    scav.attack("Bandit");
    scav.takeDamage(20);
    scav.beRepaired(10);
    scav.guardGate();
    scav.takeDamage(100);
    scav.attack("Bandit");
    return 0;
}
