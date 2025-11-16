#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

class PhoneBook
{
private:
    Contact contacts[8];
    int     nextIndex;
    int     size;

public:
    PhoneBook();
	~PhoneBook();
    void addContact();
    void searchContact() const;
};

#endif
