#ifndef AANIMAL_HPP
#define AANIMAL_HPP
#include <string>
#include <iostream>

class AAnimal
{
    protected:
        std::string _type;
    public:
        // Canonical form
        AAnimal();
        AAnimal(const AAnimal &other);
        AAnimal &operator=(const AAnimal &other);
        virtual ~AAnimal();
        // Getter
        std::string getType() const;
        // Pure virtual member function
        virtual void makeSound() const = 0;
};

#endif