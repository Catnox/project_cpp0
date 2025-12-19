#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// Default constructor
Intern::Intern()
{
	std::cout << "Intern default constructor called" << std::endl;
}

// Copy constructor
Intern::Intern(const Intern& other)
{
	std::cout << "Intern copy constructor called" << std::endl;
	(void)other;
}

// Copy assignment operator
Intern& Intern::operator=(const Intern& other)
{
	std::cout << "Intern copy assignment operator called" << std::endl;
	(void)other;
	return *this;
}

// Destructor
Intern::~Intern()
{
	std::cout << "Intern destructor called" << std::endl;
}

// Private form creation methods
AForm* Intern::createShrubberyCreationForm(const std::string& target) const
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyRequestForm(const std::string& target) const
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialPardonForm(const std::string& target) const
{
	return new PresidentialPardonForm(target);
}

// Make form function - uses array of form names and function pointers
AForm* Intern::makeForm(const std::string& formName, const std::string& target)
{
	// Array of form names
	const std::string formNames[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	// Array of corresponding creation functions
	FormCreator formCreators[] = {
		&Intern::createShrubberyCreationForm,
		&Intern::createRobotomyRequestForm,
		&Intern::createPresidentialPardonForm
	};

	// Number of forms
	const int numForms = 3;

	// Search for matching form name
	for (int i = 0; i < numForms; i++)
	{
		if (formName == formNames[i])
		{
			AForm* form = (this->*formCreators[i])(target);
			std::cout << "Intern creates " << form->getName() << std::endl;
			return form;
		}
	}

	// Form not found
	std::cout << "Intern couldn't create form: \"" << formName << "\" does not exist." << std::endl;
	throw FormNotFoundException();
}

// Exception implementation
const char* Intern::FormNotFoundException::what() const throw()
{
	return "Form not found!";
}
