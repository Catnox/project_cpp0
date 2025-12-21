#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign;
		const int			_gradeToExecute;

	public:
		// Orthodox Canonical Form
		Form();
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		// Custom constructor
		Form(const std::string& name, int gradeToSign, int gradeToExecute);

		// Getters
		const std::string&	getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;

		// Member functions
		void	beSigned(const Bureaucrat& bureaucrat);

		// Exception classes
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

// Insertion operator overload
std::ostream& operator<<(std::ostream& os, const Form& form);

#endif
