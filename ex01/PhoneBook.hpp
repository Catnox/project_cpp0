#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

class PhoneBook
{
private:
    Contact _contacts[8];
    int     _nextIndex;
    int     _size;

public:
    PhoneBook();
	~PhoneBook();
    void addContact();
    void searchContact() const;
};

#endif
