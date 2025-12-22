#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>

template<typename T>
class MutantStack : public std::stack<T>
{
public:
	// Constructeurs et destructeur
	MutantStack();
	MutantStack(MutantStack const &src);
	MutantStack &operator=(MutantStack const &rhs);
	~MutantStack();

	// Types d'itérateurs exposés depuis le container sous-jacent
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

	// Méthodes pour obtenir les itérateurs
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	// Itérateurs inversés
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
};

#include "MutantStack.tpp"

#endif
