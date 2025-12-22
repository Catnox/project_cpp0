#include <iostream>
#include <list>
#include "MutantStack.hpp"

void testMutantStack()
{
	std::cout << "=== Test MutantStack (sujet) ===" << std::endl;

	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << mstack.top() << std::endl;

	mstack.pop();

	std::cout << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
}

void testList()
{
	std::cout << std::endl << "=== Test std::list (comparaison) ===" << std::endl;

	std::list<int> lst;

	lst.push_back(5);
	lst.push_back(17);

	std::cout << lst.back() << std::endl;

	lst.pop_back();

	std::cout << lst.size() << std::endl;

	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	//[...]
	lst.push_back(0);

	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();

	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

int main()
{
	testMutantStack();
	testList();

	std::cout << std::endl << "=== Tests supplémentaires ===" << std::endl;
	{
		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++)
			mstack.push(i);

		std::cout << "Stack content: ";
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Reverse order: ";
		for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
			std::cout << *rit << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test avec strings ===" << std::endl;
	{
		MutantStack<std::string> mstack;
		mstack.push("Hello");
		mstack.push("World");
		mstack.push("42");
		mstack.push("Paris");

		std::cout << "String stack: ";
		for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Top: " << mstack.top() << std::endl;
		std::cout << "Size: " << mstack.size() << std::endl;
	}

	std::cout << std::endl << "=== Test copie ===" << std::endl;
	{
		MutantStack<int> original;
		original.push(1);
		original.push(2);
		original.push(3);

		MutantStack<int> copy(original);
		MutantStack<int> assigned;
		assigned = original;

		original.push(100);

		std::cout << "Original: ";
		for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Copy: ";
		for (MutantStack<int>::iterator it = copy.begin(); it != copy.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Assigned: ";
		for (MutantStack<int>::iterator it = assigned.begin(); it != assigned.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test const ===" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(10);
		mstack.push(20);
		mstack.push(30);

		MutantStack<int> const &constRef = mstack;

		std::cout << "Const iteration: ";
		for (MutantStack<int>::const_iterator it = constRef.begin(); it != constRef.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	return 0;
}
