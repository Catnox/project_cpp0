#include "Brain.hpp"

// Canonical form
Brain::Brain()
{
    std::cout << "Brain Default constructed." << std::endl;
}

Brain::Brain(const Brain &other)
{
    for (int i = 0; i < 100; ++i) {
        ideas[i] = other.ideas[i];
    }
    std::cout << "Brain copy constructed." << std::endl;
}

Brain &Brain::operator=(const Brain &other)
{
    if (this != &other) {
        for (int i = 0; i < 100; ++i) {
            ideas[i] = other.ideas[i];
        }
    }
    return *this;
}

Brain::~Brain()
{
    std::cout << "Brain destructed." << std::endl;
}

// Setter
void Brain::setIdea(int index, const std::string &idea)
{
    if (index >= 0 && index < 100)
        ideas[index] = idea;
}

// Getter
std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100)
        return ideas[index];
    return "";
}
