#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <iostream>
#include "AForm.hpp"

class Intern
{
	private:
		// Function pointer type for form creation
		typedef AForm* (Intern::*FormCreator)(const std::string& target) const;

		// Form creation methods
		AForm*	createShrubberyCreationForm(const std::string& target) const;
		AForm*	createRobotomyRequestForm(const std::string& target) const;
		AForm*	createPresidentialPardonForm(const std::string& target) const;

	public:
		// Orthodox Canonical Form
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		// Member function
		AForm*	makeForm(const std::string& formName, const std::string& target);

		// Exception class
		class FormNotFoundException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif
