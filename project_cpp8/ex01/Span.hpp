#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <algorithm>

class Span
{
private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

public:
	// Constructeurs et destructeur
	Span();
	Span(unsigned int n);
	Span(Span const &src);
	Span &operator=(Span const &rhs);
	~Span();

	// Méthodes membres
	void	addNumber(int number);
	int		shortestSpan() const;
	int		longestSpan() const;

	// Méthode template pour ajouter une range d'itérateurs
	template<typename InputIterator>
	void addRange(InputIterator begin, InputIterator end)
	{
		size_t distance = std::distance(begin, end);
		if (_numbers.size() + distance > _maxSize)
			throw SpanFullException();
		_numbers.insert(_numbers.end(), begin, end);
	}

	// Getters
	unsigned int getSize() const;
	unsigned int getMaxSize() const;

	// Exceptions
	class SpanFullException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class NoSpanException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
