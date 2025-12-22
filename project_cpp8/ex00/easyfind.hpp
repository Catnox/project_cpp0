#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

class NotFoundException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "Element not found in container";
	}
};

// Fonction template easyfind
// Trouve la première occurrence d'un entier dans un container
template<typename T>
typename T::iterator easyfind(T &container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw NotFoundException();
	return it;
}

// Version const
template<typename T>
typename T::const_iterator easyfind(T const &container, int value)
{
	typename T::const_iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw NotFoundException();
	return it;
}

#endif
