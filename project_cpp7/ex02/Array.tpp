#ifndef ARRAY_TPP
#define ARRAY_TPP

// Constructeur par défaut
template<typename T>
Array<T>::Array() : _elements(NULL), _size(0)
{
}

// Constructeur avec taille
template<typename T>
Array<T>::Array(unsigned int n) : _elements(new T[n]()), _size(n)
{
}

// Constructeur de copie (deep copy)
template<typename T>
Array<T>::Array(Array const &src) : _elements(NULL), _size(0)
{
	*this = src;
}

// Opérateur d'assignation (deep copy)
template<typename T>
Array<T> &Array<T>::operator=(Array const &rhs)
{
	if (this != &rhs)
	{
		if (_elements)
			delete[] _elements;
		_size = rhs._size;
		if (_size > 0)
		{
			_elements = new T[_size]();
			for (unsigned int i = 0; i < _size; i++)
				_elements[i] = rhs._elements[i];
		}
		else
			_elements = NULL;
	}
	return *this;
}

// Destructeur
template<typename T>
Array<T>::~Array()
{
	if (_elements)
		delete[] _elements;
}

// Opérateur [] (non-const)
template<typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _elements[index];
}

// Opérateur [] (const)
template<typename T>
T const &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _elements[index];
}

// Fonction size()
template<typename T>
unsigned int Array<T>::size() const
{
	return _size;
}

// Exception message
template<typename T>
const char *Array<T>::OutOfBoundsException::what() const throw()
{
	return "Index out of bounds";
}

#endif
