#include "PhoneBook.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

PhoneBook::PhoneBook() : nextIndex(0), size(0) {}

PhoneBook::~PhoneBook() {}

void PhoneBook::addContact()
{
    contacts[nextIndex].setInfo();
    nextIndex = (nextIndex + 1) % 8;
    if (size < 8)
        size++;
}

void PhoneBook::searchContact() const
{
    if (size == 0)
	{
        std::cout << "PhoneBook is empty." << std::endl;
        return;
    }
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;

    for (int i = 0; i < size; i++)
        contacts[i].displayShort(i);

    std::cout << "Enter index to view details: ";
    int index;
    if (!(std::cin >> index))
	{
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input." << std::endl;
        return;
    }
    std::cin.ignore();
    if (index < 0 || index >= size)
	{
        std::cout << "Invalid index." << std::endl;
    }
	else
	{
        contacts[index].displayFull();
    }
}
