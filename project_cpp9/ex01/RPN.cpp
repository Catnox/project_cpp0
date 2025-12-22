#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

// Constructeur par défaut
RPN::RPN()
{
}

// Constructeur de copie
RPN::RPN(RPN const &src) : _stack(src._stack)
{
}

// Opérateur d'assignation
RPN &RPN::operator=(RPN const &rhs)
{
	if (this != &rhs)
		_stack = rhs._stack;
	return *this;
}

// Destructeur
RPN::~RPN()
{
}

// Vérifier si c'est un opérateur
bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Appliquer l'opérateur
int RPN::applyOperator(int a, int b, char op) const
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw DivisionByZeroException();
			return a / b;
		default:
			throw InvalidExpressionException();
	}
}

// Calculer l'expression RPN
int RPN::calculate(std::string const &expression)
{
	// Vider la stack
	while (!_stack.empty())
		_stack.pop();

	for (size_t i = 0; i < expression.length(); i++)
	{
		char c = expression[i];

		// Ignorer les espaces
		if (c == ' ')
			continue;

		// Si c'est un chiffre (0-9)
		if (std::isdigit(c))
		{
			_stack.push(c - '0');
		}
		// Si c'est un opérateur
		else if (isOperator(c))
		{
			if (_stack.size() < 2)
				throw InvalidExpressionException();

			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();

			int result = applyOperator(a, b, c);
			_stack.push(result);
		}
		// Caractère invalide
		else
		{
			throw InvalidExpressionException();
		}
	}

	// À la fin, il ne doit rester qu'un seul élément
	if (_stack.size() != 1)
		throw InvalidExpressionException();

	return _stack.top();
}

// Exceptions
const char *RPN::InvalidExpressionException::what() const throw()
{
	return "Error";
}

const char *RPN::DivisionByZeroException::what() const throw()
{
	return "Error: division by zero";
}
