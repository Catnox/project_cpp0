#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "=== Test 1: FragTrap construction and actions ===" << std::endl;
    FragTrap f1;
    FragTrap f2("fraggy");
    f1.attack("target1");
    f2.attack("target2");
    f2.takeDamage(30);
    f2.beRepaired(20);
    f2.highFivesGuys();
    f2.takeDamage(100);
    f2.attack("ennemy");

    std::cout << "\n=== Test 2: FragTrap copy and assignment ===" << std::endl;
    FragTrap f3(f2);
    f3.attack("copyTarget");
    FragTrap f4;
    f4 = f2;
    f4.attack("assignedTarget");

    std::cout << "\n=== Test 3: FragTrap energy exhaustion ===" << std::endl;
    FragTrap f5("TiredFrag");
    for (int i = 0; i < 105; ++i) {
        f5.attack("dummy");
    }
    f5.beRepaired(5);

    return 0;
}
