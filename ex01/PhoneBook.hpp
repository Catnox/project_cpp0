/* #ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP
#include "Contact.hpp"
#define MAX_CONTACTS 8

class PhoneBook
{
	private :
		Contact	_contacts[MAX_CONTACTS];
		int		_numContacts;
		void	print() const;
	public :
				PhoneBook();
				~PhoneBook();
		void	addContact();
		void	search() const;
};

#endif */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
private:
    Contact contacts[8];
    int     nextIndex;
    int     size;

public:
    PhoneBook();
    void addContact();
    void searchContact() const;
};

#endif
