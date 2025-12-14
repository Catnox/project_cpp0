#ifndef BRAIN_HPP
#define BRAIN_HPP
#include <string>
#include <iostream>

class Brain
{
    private:
        std::string ideas[100];
    public:
        // Canonical form
        Brain();
        Brain(const Brain &other);
        Brain &operator=(const Brain &other);
        ~Brain();
        // Setter
        void setIdea(int index, const std::string &idea);
        // Getter
        std::string getIdea(int index) const;
};

#endif