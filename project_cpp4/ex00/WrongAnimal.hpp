#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP
#include <string>
#include <iostream>

class WrongAnimal
{
    protected:
        std::string _type;
    public:
        // Canonical form
        WrongAnimal();
        WrongAnimal(const WrongAnimal &other);
        WrongAnimal &operator=(const WrongAnimal &other);
        ~WrongAnimal();
        // Getter
        std::string getType() const;
        // Member function
        void makeSound() const;
};

#endif
