#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <string>
#include <iostream>

class Animal
{
    protected:
        std::string _type;
    public:
        // Canonical form
        Animal();
        Animal(const Animal &other);
        Animal &operator=(const Animal &other);
        virtual ~Animal();
        // Getter
        std::string getType() const;
        // Member functions
        virtual void makeSound() const;
};

#endif