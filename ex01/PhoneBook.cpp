#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _nextIndex(0), _size(0)
{
    std::cout << "PhoneBook constructor called" << std::endl;
}

PhoneBook::~PhoneBook()
{
    std::cout << "PhoneBook destructor called" << std::endl;
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
    std::string line;
    if (!std::getline(std::cin, line))
        return;

    if (line.size() != 1 || line[0] < '0' || line[0] > '7')
    {
        std::cout << "Invalid input." << std::endl;
        return;
    }
    
    int index = line[0] - '0';
    if (index >= _size)
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }
    _contacts[index].displayFull();
}
