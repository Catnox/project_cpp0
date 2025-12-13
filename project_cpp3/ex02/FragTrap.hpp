#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
    // Canonical form
    FragTrap();
    FragTrap(const FragTrap &other);
    FragTrap &operator=(const FragTrap &other);
    ~FragTrap();
    // Additional constructor
    FragTrap(const std::string &name);
    // Member functions
    void attack(const std::string &target);
    void highFivesGuys();
};

#endif
