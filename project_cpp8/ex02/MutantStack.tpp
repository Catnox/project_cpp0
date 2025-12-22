#ifndef MUTANTSTACK_TPP
#define MUTANTSTACK_TPP

// Constructeur par défaut
template<typename T>
MutantStack<T>::MutantStack() : std::stack<T>()
{
}

// Constructeur de copie
template<typename T>
MutantStack<T>::MutantStack(MutantStack const &src) : std::stack<T>(src)
{
}

// Opérateur d'assignation
template<typename T>
MutantStack<T> &MutantStack<T>::operator=(MutantStack const &rhs)
{
	if (this != &rhs)
		std::stack<T>::operator=(rhs);
	return *this;
}

// Destructeur
template<typename T>
MutantStack<T>::~MutantStack()
{
}

// Itérateurs normaux
template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
	return this->c.end();
}

template<typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const
{
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const
{
	return this->c.end();
}

// Itérateurs inversés
template<typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin()
{
	return this->c.rbegin();
}

template<typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend()
{
	return this->c.rend();
}

template<typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const
{
	return this->c.rbegin();
}

template<typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const
{
	return this->c.rend();
}

#endif
