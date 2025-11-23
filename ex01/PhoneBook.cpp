#include "PhoneBook.hpp"
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cctype>

PhoneBook::PhoneBook() : _nextIndex(0), _size(0)
{
    std::cout << "Constructor called" << std::endl;
}

PhoneBook::~PhoneBook()
{
    std::cout << "Destructor called" << std::endl;
}

void PhoneBook::addContact()
{
    if (!_contacts[_nextIndex].setInfo())
        return;

    _nextIndex = (_nextIndex + 1) % 8;
    if (_size < 8)
        _size++;
}

void PhoneBook::searchContact() const
{
    if (_size == 0)
	{
        std::cout << "PhoneBook is empty." << std::endl;
        return;
    }
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;

    for (int i = 0; i < _size; i++)
        _contacts[i].displayShort(i);

    std::cout << "Enter index to view details: ";
    int index;
    std::string line;
    if (!std::getline(std::cin, line)) {
        return;
    }

    // Use strtol to parse the integer and detect invalid chars / overflow
    const char *cstr = line.c_str();
    char *endptr = NULL;
    errno = 0;
    long val = std::strtol(cstr, &endptr, 10);
    if (endptr == cstr) {
        // no conversion performed
        std::cout << "Invalid input." << std::endl;
        return;
    }
    // skip trailing whitespace
    while (*endptr && std::isspace(static_cast<unsigned char>(*endptr)))
        ++endptr;
    if (*endptr != '\0') {
        // leftover non-space characters
        std::cout << "Invalid input." << std::endl;
        return;
    }
    if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        // out of int range
        std::cout << "Invalid input." << std::endl;
        return;
    }
    index = static_cast<int>(val);
    if (index < 0 || index >= _size)
    {
        std::cout << "Invalid index." << std::endl;
    }
    else
    {
        _contacts[index].displayFull();
    }
}
