#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	// Seed random number generator for RobotomyRequestForm
	std::srand(std::time(NULL));

	std::cout << "========================================" << std::endl;
	std::cout << "=== Test 1: ShrubberyCreationForm ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Bureaucrat gardener("Gardener", 130);
		ShrubberyCreationForm shrubForm("home");
		std::cout << gardener << std::endl;
		std::cout << shrubForm << std::endl;
		
		// Try to execute without signing
		std::cout << "\n--- Trying to execute without signing ---" << std::endl;
		gardener.executeForm(shrubForm);
		
		// Sign and execute
		std::cout << "\n--- Signing and executing ---" << std::endl;
		gardener.signForm(shrubForm);
		gardener.executeForm(shrubForm);
		std::cout << "Check for 'home_shrubbery' file!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 2: RobotomyRequestForm ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Bureaucrat engineer("Engineer", 40);
		RobotomyRequestForm robotForm("Bender");
		std::cout << engineer << std::endl;
		std::cout << robotForm << std::endl;
		
		engineer.signForm(robotForm);
		std::cout << "\n--- Executing multiple times (50% success rate) ---" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << "\nAttempt " << i + 1 << ":" << std::endl;
			engineer.executeForm(robotForm);
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 3: PresidentialPardonForm ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardonForm("Arthur Dent");
		std::cout << president << std::endl;
		std::cout << pardonForm << std::endl;
		
		president.signForm(pardonForm);
		president.executeForm(pardonForm);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 4: Grade too low to sign ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardonForm("Marvin");
		std::cout << intern << std::endl;
		std::cout << pardonForm << std::endl;
		
		intern.signForm(pardonForm);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 5: Grade too low to execute ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 20);
		Bureaucrat worker("Worker", 50);
		PresidentialPardonForm pardonForm("Ford Prefect");
		std::cout << boss << std::endl;
		std::cout << worker << std::endl;
		std::cout << pardonForm << std::endl;
		
		// Boss can sign (grade 20 <= 25)
		boss.signForm(pardonForm);
		// Worker cannot execute (grade 50 > 5)
		worker.executeForm(pardonForm);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "=== Test 6: Edge cases ===" << std::endl;
	std::cout << "========================================" << std::endl;
	try
	{
		// Exact grade match for signing
		Bureaucrat exactSign("ExactSign", 145);
		ShrubberyCreationForm shrubForm2("garden");
		std::cout << exactSign << std::endl;
		std::cout << shrubForm2 << std::endl;
		exactSign.signForm(shrubForm2);
		
		// Grade too low to execute (need 137, has 145)
		std::cout << "\n--- ExactSign tries to execute (needs 137, has 145) ---" << std::endl;
		exactSign.executeForm(shrubForm2);
		
		// Another bureaucrat executes
		Bureaucrat executor("Executor", 137);
		std::cout << "\n--- Executor tries (has exactly 137) ---" << std::endl;
		executor.executeForm(shrubForm2);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
