#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:
		std::string	_target;

	public:
		// Orthodox Canonical Form
		ShrubberyCreationForm();
		ShrubberyCreationForm(const ShrubberyCreationForm& other);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
		virtual ~ShrubberyCreationForm();

		// Custom constructor
		ShrubberyCreationForm(const std::string& target);

		// Getter
		const std::string&	getTarget() const;

		// Override executeAction
		virtual void	executeAction() const;
};

#endif
