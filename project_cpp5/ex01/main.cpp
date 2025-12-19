#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "=== Test 1: Creating valid Form ===" << std::endl;
	try
	{
		Form taxForm("Tax Form", 50, 25);
		std::cout << taxForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 2: Form grade too high (0) ===" << std::endl;
	try
	{
		Form invalidForm("Invalid", 0, 50);
		std::cout << invalidForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 3: Form grade too low (151) ===" << std::endl;
	try
	{
		Form invalidForm("Invalid", 50, 151);
		std::cout << invalidForm << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 4: Bureaucrat signs form successfully ===" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 30);
		Form contract("Contract", 50, 25);
		std::cout << bob << std::endl;
		std::cout << contract << std::endl;
		bob.signForm(contract);
		std::cout << contract << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 5: Bureaucrat cannot sign form (grade too low) ===" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 100);
		Form topSecret("Top Secret", 10, 5);
		std::cout << intern << std::endl;
		std::cout << topSecret << std::endl;
		intern.signForm(topSecret);
		std::cout << topSecret << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 6: Edge case - exact grade match ===" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 50);
		Form permit("Permit", 50, 50);
		std::cout << alice << std::endl;
		std::cout << permit << std::endl;
		alice.signForm(permit);
		std::cout << permit << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 7: Edge case - one grade below requirement ===" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 51);
		Form license("License", 50, 50);
		std::cout << charlie << std::endl;
		std::cout << license << std::endl;
		charlie.signForm(license);
		std::cout << license << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test 8: Copy constructor ===" << std::endl;
	try
	{
		Form original("Original Form", 42, 21);
		std::cout << "Original: " << original << std::endl;
		Form copy(original);
		std::cout << "Copy: " << copy << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
