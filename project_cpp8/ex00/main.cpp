#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main(void)
{
	std::cout << "=== Test avec std::vector ===" << std::endl;
	{
		std::vector<int> vec;
		for (int i = 0; i < 10; i++)
			vec.push_back(i * 2);

		std::cout << "Vector: ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			std::vector<int>::iterator it = easyfind(vec, 6);
			std::cout << "Found 6 at position: " << std::distance(vec.begin(), it) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			std::vector<int>::iterator it = easyfind(vec, 42);
			std::cout << "Found 42 at position: " << std::distance(vec.begin(), it) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "42: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test avec std::list ===" << std::endl;
	{
		std::list<int> lst;
		for (int i = 5; i >= 0; i--)
			lst.push_back(i);

		std::cout << "List: ";
		for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			std::list<int>::iterator it = easyfind(lst, 3);
			std::cout << "Found 3 at position: " << std::distance(lst.begin(), it) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			std::list<int>::iterator it = easyfind(lst, 10);
			std::cout << "Found 10 at position: " << std::distance(lst.begin(), it) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "10: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test avec std::deque ===" << std::endl;
	{
		std::deque<int> deq;
		deq.push_back(100);
		deq.push_back(200);
		deq.push_back(300);
		deq.push_back(400);
		deq.push_back(500);

		std::cout << "Deque: ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		try
		{
			std::deque<int>::iterator it = easyfind(deq, 300);
			std::cout << "Found 300 at position: " << std::distance(deq.begin(), it) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test avec const container ===" << std::endl;
	{
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		
		std::vector<int> const &constVec = vec;

		try
		{
			std::vector<int>::const_iterator it = easyfind(constVec, 2);
			std::cout << "Found 2 in const vector at position: " << std::distance(constVec.begin(), it) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
