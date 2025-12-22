#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
private:
	std::stack<int>	_stack;

	bool	isOperator(char c) const;
	int		applyOperator(int a, int b, char op) const;

public:
	// Constructeurs et destructeur
	RPN();
	RPN(RPN const &src);
	RPN &operator=(RPN const &rhs);
	~RPN();

	// Méthode principale
	int calculate(std::string const &expression);

	// Exceptions
	class InvalidExpressionException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class DivisionByZeroException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
