/* #include <iostream>
#include <string>
#include "Contact.hpp"
#include "PhoneBook.hpp"

int main()
{
	PhoneBook	phoneBook;
	std::string	entry;

	while (entry != "EXIT")
	{
		std::cout << "enter a command : ";
		std::getline(std::cin, entry);
		if (std::cin.eof())
			exit(0);
		if (entry == "ADD")
			phoneBook.addContact();
		else if (entry == "SEARCH")
			phoneBook.search();
	}
	return 0;
} */

#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main() {
    PhoneBook book;
    std::string command;

    std::cout << "Welcome to My Awesome PhoneBook!" << std::endl;
    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command))
            break;
        if (command == "ADD")
            book.addContact();
        else if (command == "SEARCH")
            book.searchContact();
        else if (command == "EXIT")
            break;
    }
    return 0;
}
