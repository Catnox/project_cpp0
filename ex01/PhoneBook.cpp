/* #include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>

PhoneBook::PhoneBook() : _numContacts(0)
{
	std::cout << "phone book created" << std::endl;
}

PhoneBook::~PhoneBook()
{
	std::cout << "phone book destroyed" << std::endl;
}

void PhoneBook::addContact()
{
	Contact	contact;
	int		i;

	i = this->_numContacts;
	if (this->_numContacts >= MAX_CONTACTS)
	{
		i = this->_numContacts % MAX_CONTACTS;
		std::cout << "warning : overwriting contact " << i + 1 << std::endl;
	}
	std::cout << "adding new contact" << std::endl;
	contact.fill();
	this->_contacts[i] = contact;
	this->_numContacts++;
}

static void printDashRow()
{
	int size = 4 * 10 + 4 + 1;
	for (int i = 0; i < size; i++)
		std::cout << "-";
	std::cout << std::endl;
}

static void printHeader()
{
	printDashRow();
	std::cout << "|     index|first name| last name|  nickname|" << std::endl;
	printDashRow();
}

static void printField(const std::string& s)
{
	std::cout << "|";
	if (s.size() > 10)
		std::cout << s.substr(0, 9) << ".";
	else
		std::cout << std::setw(10) << s;
}

static void printField(int i)
{
	std::cout << "|";
	std::cout << std::setw(10) << i;
}

void PhoneBook::print() const
{
	printHeader();
	for (int i = 0; i < this->_numContacts && i < MAX_CONTACTS; i++)
	{
		printField(i + 1);
		printField(this->_contacts[i].getFirstName());
		printField(this->_contacts[i].getLastName());
		printField(this->_contacts[i].getNickname());
		std::cout << "|" << std::endl;
		printDashRow();
	}
}

static bool str_is_digit(const std::string& s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (!std::isdigit(s[i]))
			return false;
	}
	return true;
}

void PhoneBook::search() const
{
	std::string	entry;
	int			i;

	if (this->_numContacts == 0)
	{
		std::cout << "no contacts" << std::endl;
		return;
	}
	this->print();
	while (true)
	{
		std::cout << "index : ";
		std::getline(std::cin, entry);
		if (std::cin.eof())
			exit(0);
		i = std::atoi(entry.c_str());
		if (!str_is_digit(entry) || i < 1 || i > this->_numContacts || i > MAX_CONTACTS)
			std::cout << "invalid index" << std::endl;
		else
		{
			this->_contacts[i - 1].print();
			break;
		}
	}
} */

#include "PhoneBook.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

PhoneBook::PhoneBook() : nextIndex(0), size(0) {}

void PhoneBook::addContact() {
    contacts[nextIndex].setInfo();
    nextIndex = (nextIndex + 1) % 8;
    if (size < 8)
        size++;
}

void PhoneBook::searchContact() const {
    if (size == 0) {
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
    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input." << std::endl;
        return;
    }
    std::cin.ignore();
    if (index < 0 || index >= size) {
        std::cout << "Invalid index." << std::endl;
    } else {
        contacts[index].displayFull();
    }
}
