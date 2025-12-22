#include <iostream>
#include <string>
#include "iter.hpp"

// Fonction template pour afficher un élément
template<typename T>
void print(T const &elem)
{
	std::cout << elem << " ";
}

// Fonction template pour incrémenter un élément (non-const)
template<typename T>
void increment(T &elem)
{
	elem++;
}

// Fonction template pour doubler un élément (non-const)
template<typename T>
void doubleValue(T &elem)
{
	elem *= 2;
}

// Fonction pour mettre en majuscule (non-const)
void toUpper(char &c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
}

int main(void)
{
	std::cout << "=== Test avec int array ===" << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

	std::cout << "Original: ";
	::iter(intArray, intLen, print<int>);
	std::cout << std::endl;

	::iter(intArray, intLen, increment<int>);
	std::cout << "After increment: ";
	::iter(intArray, intLen, print<int>);
	std::cout << std::endl;

	::iter(intArray, intLen, doubleValue<int>);
	std::cout << "After double: ";
	::iter(intArray, intLen, print<int>);
	std::cout << std::endl;

	std::cout << std::endl << "=== Test avec double array ===" << std::endl;
	double doubleArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	size_t doubleLen = sizeof(doubleArray) / sizeof(doubleArray[0]);

	std::cout << "Original: ";
	::iter(doubleArray, doubleLen, print<double>);
	std::cout << std::endl;

	::iter(doubleArray, doubleLen, doubleValue<double>);
	std::cout << "After double: ";
	::iter(doubleArray, doubleLen, print<double>);
	std::cout << std::endl;

	std::cout << std::endl << "=== Test avec string array ===" << std::endl;
	std::string strArray[] = {"Hello", "World", "42", "Paris"};
	size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

	std::cout << "Strings: ";
	::iter(strArray, strLen, print<std::string>);
	std::cout << std::endl;

	std::cout << std::endl << "=== Test avec char array ===" << std::endl;
	char charArray[] = {'h', 'e', 'l', 'l', 'o'};
	size_t charLen = sizeof(charArray) / sizeof(charArray[0]);

	std::cout << "Original: ";
	::iter(charArray, charLen, print<char>);
	std::cout << std::endl;

	::iter(charArray, charLen, toUpper);
	std::cout << "After toUpper: ";
	::iter(charArray, charLen, print<char>);
	std::cout << std::endl;

	std::cout << std::endl << "=== Test avec const array ===" << std::endl;
	int const constArray[] = {10, 20, 30, 40, 50};
	size_t constLen = sizeof(constArray) / sizeof(constArray[0]);

	std::cout << "Const array: ";
	::iter(constArray, constLen, print<int>);
	std::cout << std::endl;

	return 0;
}
