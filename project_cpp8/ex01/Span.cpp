#include "Span.hpp"
#include <climits>

// Constructeur par défaut
Span::Span() : _maxSize(0)
{
}

// Constructeur avec taille
Span::Span(unsigned int n) : _maxSize(n)
{
}

// Constructeur de copie
Span::Span(Span const &src) : _maxSize(src._maxSize), _numbers(src._numbers)
{
}

// Opérateur d'assignation
Span &Span::operator=(Span const &rhs)
{
	if (this != &rhs)
	{
		_maxSize = rhs._maxSize;
		_numbers = rhs._numbers;
	}
	return *this;
}

// Destructeur
Span::~Span()
{
}

// Ajouter un nombre
void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw SpanFullException();
	_numbers.push_back(number);
}

// Trouver le plus petit écart
int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());

	int minSpan = INT_MAX;
	for (size_t i = 1; i < sorted.size(); i++)
	{
		int span = sorted[i] - sorted[i - 1];
		if (span < minSpan)
			minSpan = span;
	}
	return minSpan;
}

// Trouver le plus grand écart
int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	int min = *std::min_element(_numbers.begin(), _numbers.end());
	int max = *std::max_element(_numbers.begin(), _numbers.end());

	return max - min;
}

// Getters
unsigned int Span::getSize() const
{
	return _numbers.size();
}

unsigned int Span::getMaxSize() const
{
	return _maxSize;
}

// Exceptions
const char *Span::SpanFullException::what() const throw()
{
	return "Span is full, cannot add more numbers";
}

const char *Span::NoSpanException::what() const throw()
{
	return "Not enough numbers to find a span (need at least 2)";
}
