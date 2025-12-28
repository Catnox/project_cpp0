#include "PresidentialPardonForm.hpp"

// Default constructor
PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", 25, 5), _target("default")
{
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}

// Copy constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other)
	: AForm(other), _target(other._target)
{
	std::cout << "PresidentialPardonForm copy constructor called" << std::endl;
}

// Copy assignment operator
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	std::cout << "PresidentialPardonForm copy assignment operator called" << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

// Destructor
PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm destructor called" << std::endl;
}

// Parameterized constructor
PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
	: AForm("PresidentialPardonForm", 25, 5), _target(target)
{
	std::cout << "PresidentialPardonForm parameterized constructor called" << std::endl;
}

// Getter
const std::string& PresidentialPardonForm::getTarget() const
{
	return _target;
}

// Execute action - presidential pardon
void PresidentialPardonForm::executeAction() const
{
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
