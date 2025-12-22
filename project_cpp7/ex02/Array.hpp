#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>

template<typename T>
class Array
{
private:
	T		*_elements;
	unsigned int	_size;

public:
	// Constructeur par défaut : tableau vide
	Array();

	// Constructeur avec taille : n éléments initialisés par défaut
	Array(unsigned int n);

	// Constructeur de copie
	Array(Array const &src);

	// Opérateur d'assignation
	Array &operator=(Array const &rhs);

	// Destructeur
	~Array();

	// Opérateur d'accès []
	T &operator[](unsigned int index);
	T const &operator[](unsigned int index) const;

	// Fonction membre size()
	unsigned int size() const;

	// Exception pour index hors limites
	class OutOfBoundsException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#include "Array.tpp"

#endif
