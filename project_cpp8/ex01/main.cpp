#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main()
{
	std::cout << "=== Test basique du sujet ===" << std::endl;
	{
		Span sp = Span(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test exception: Span plein ===" << std::endl;
	{
		Span sp(3);
		try
		{
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
			sp.addNumber(4); // Doit lancer une exception
		}
		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test exception: Pas assez de nombres ===" << std::endl;
	{
		Span sp(5);
		try
		{
			sp.addNumber(42);
			std::cout << sp.shortestSpan() << std::endl; // Doit lancer une exception
		}
		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}

		Span empty(5);
		try
		{
			std::cout << empty.longestSpan() << std::endl; // Doit lancer une exception
		}
		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test avec 10,000 nombres ===" << std::endl;
	{
		Span sp(10000);
		srand(time(NULL));

		for (int i = 0; i < 10000; i++)
			sp.addNumber(rand());

		std::cout << "Size: " << sp.getSize() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test avec 100,000 nombres ===" << std::endl;
	{
		Span sp(100000);

		for (int i = 0; i < 100000; i++)
			sp.addNumber(rand());

		std::cout << "Size: " << sp.getSize() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test addRange avec vector ===" << std::endl;
	{
		Span sp(10);
		std::vector<int> vec;
		for (int i = 0; i < 5; i++)
			vec.push_back(i * 10);

		std::cout << "Vector: ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		sp.addRange(vec.begin(), vec.end());
		std::cout << "Span size after addRange: " << sp.getSize() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test addRange avec list ===" << std::endl;
	{
		Span sp(20);
		std::list<int> lst;
		for (int i = 100; i >= 0; i -= 10)
			lst.push_back(i);

		std::cout << "List: ";
		for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		sp.addRange(lst.begin(), lst.end());
		std::cout << "Span size after addRange: " << sp.getSize() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test addRange: dépassement ===" << std::endl;
	{
		Span sp(5);
		std::vector<int> vec;
		for (int i = 0; i < 10; i++)
			vec.push_back(i);

		try
		{
			sp.addRange(vec.begin(), vec.end()); // Doit lancer une exception
		}
		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test copie et assignation ===" << std::endl;
	{
		Span sp1(5);
		sp1.addNumber(1);
		sp1.addNumber(2);
		sp1.addNumber(3);

		Span sp2(sp1); // Copie
		Span sp3 = sp1; // Assignation

		sp1.addNumber(100);

		std::cout << "sp1 size: " << sp1.getSize() << ", longest: " << sp1.longestSpan() << std::endl;
		std::cout << "sp2 size: " << sp2.getSize() << ", longest: " << sp2.longestSpan() << std::endl;
		std::cout << "sp3 size: " << sp3.getSize() << ", longest: " << sp3.longestSpan() << std::endl;
	}

	return 0;
}
