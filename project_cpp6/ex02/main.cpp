#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Generate a random instance of A, B, or C
Base* generate(void)
{
	int random = std::rand() % 3;
	
	switch (random)
	{
		case 0:
			std::cout << "Generated: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated: B" << std::endl;
			return new B();
		default:
			std::cout << "Generated: C" << std::endl;
			return new C();
	}
}

// Identify type using pointer
// dynamic_cast returns nullptr if cast fails
void identify(Base* p)
{
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

// Identify type using reference
// dynamic_cast throws std::bad_cast if cast fails (but we can't use typeinfo header)
// So we use try/catch with a reference cast
void identify(Base& p)
{
	// Try A
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (...) {}
	
	// Try B
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (...) {}
	
	// Try C
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (...) {}
	
	std::cout << "Unknown type" << std::endl;
}

int main()
{
	// Seed random number generator
	std::srand(std::time(NULL));

	std::cout << "=== Test 1: Generate and identify with pointer ===" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "\nTest " << i + 1 << ": ";
		Base* ptr = generate();
		std::cout << "Identified (ptr): ";
		identify(ptr);
		std::cout << "Identified (ref): ";
		identify(*ptr);
		delete ptr;
	}

	std::cout << "\n=== Test 2: Known types ===" << std::endl;
	
	Base* a = new A();
	Base* b = new B();
	Base* c = new C();

	std::cout << "\nA object:" << std::endl;
	std::cout << "  identify(ptr): ";
	identify(a);
	std::cout << "  identify(ref): ";
	identify(*a);

	std::cout << "\nB object:" << std::endl;
	std::cout << "  identify(ptr): ";
	identify(b);
	std::cout << "  identify(ref): ";
	identify(*b);

	std::cout << "\nC object:" << std::endl;
	std::cout << "  identify(ptr): ";
	identify(c);
	std::cout << "  identify(ref): ";
	identify(*c);

	delete a;
	delete b;
	delete c;

	std::cout << "\n=== Test 3: Null pointer ===" << std::endl;
	std::cout << "identify(NULL): ";
	identify(static_cast<Base*>(NULL));

	return 0;
}
