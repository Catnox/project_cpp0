#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
	private:
		std::string	_target;

	public:
		// Orthodox Canonical Form
		RobotomyRequestForm();
		RobotomyRequestForm(const RobotomyRequestForm& other);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
		virtual ~RobotomyRequestForm();

		// Custom constructor
		RobotomyRequestForm(const std::string& target);

		// Getter
		const std::string&	getTarget() const;

		// Override executeAction
		virtual void	executeAction() const;
};

#endif
