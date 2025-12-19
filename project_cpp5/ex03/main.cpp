#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	// Seed random number generator for RobotomyRequestForm
	std::srand(std::time(NULL));

	std::cout << "========================================" << std::endl;
	std::cout << "=== Test 1: Intern creates RobotomyRequestForm ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Intern someRandomIntern;
		AForm* rrf;
		
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		std::cout << *rrf << std::endl;
		
		Bureaucrat engineer("Engineer", 40);
		engineer.signForm(*rrf);
		engineer.executeForm(*rrf);
		
		delete rrf;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 2: Intern creates ShrubberyCreationForm ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Intern intern;
		AForm* shrubForm;
		
		shrubForm = intern.makeForm("shrubbery creation", "garden");
		std::cout << *shrubForm << std::endl;
		
		Bureaucrat gardener("Gardener", 130);
		gardener.signForm(*shrubForm);
		gardener.executeForm(*shrubForm);
		
		delete shrubForm;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 3: Intern creates PresidentialPardonForm ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Intern intern;
		AForm* pardonForm;
		
		pardonForm = intern.makeForm("presidential pardon", "Marvin");
		std::cout << *pardonForm << std::endl;
		
		Bureaucrat president("President", 1);
		president.signForm(*pardonForm);
		president.executeForm(*pardonForm);
		
		delete pardonForm;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 4: Intern tries to create unknown form ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Intern intern;
		AForm* unknownForm;
		
		unknownForm = intern.makeForm("coffee request", "office");
		std::cout << *unknownForm << std::endl;
		
		delete unknownForm;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 5: Full workflow ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Intern intern;
		Bureaucrat boss("Boss", 1);
		
		// Create all three forms
		AForm* forms[3];
		forms[0] = intern.makeForm("shrubbery creation", "office");
		forms[1] = intern.makeForm("robotomy request", "Wall-E");
		forms[2] = intern.makeForm("presidential pardon", "Arthur Dent");
		
		std::cout << "\n--- Signing and executing all forms ---" << std::endl;
		for (int i = 0; i < 3; i++)
		{
			std::cout << "\n";
			boss.signForm(*forms[i]);
			boss.executeForm(*forms[i]);
		}
		
		// Clean up
		for (int i = 0; i < 3; i++)
			delete forms[i];
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 6: Intern Orthodox Canonical Form ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Intern intern1;
		Intern intern2(intern1);
		Intern intern3;
		intern3 = intern1;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
