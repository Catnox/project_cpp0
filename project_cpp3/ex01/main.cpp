#include "ScavTrap.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Test 1: Default construction and named construction ===" << std::endl;
    ScavTrap s1;
    ScavTrap s2("scavy");
    s1.attack("ennemy");
    s2.attack("ennemy");

    std::cout << "\n=== Test 2: Damage and repair ===" << std::endl;
    s2.takeDamage(30);
    s2.beRepaired(15);
    s2.takeDamage(90);
    s2.beRepaired(10);
    s2.attack("shouldFail");

    std::cout << "\n=== Test 3: Energy exhaustion ===" << std::endl;
    ScavTrap s5("Tired");
    for (int i = 0; i < 55; ++i) {
        s5.attack("dummy");
    }
    s5.beRepaired(5);

    std::cout << "\n=== Test 4: Guard Gate mode ===" << std::endl;
    ScavTrap s6("Guardian");
    s6.guardGate();
    s6.takeDamage(50);
    s6.guardGate();

    return 0;
}
