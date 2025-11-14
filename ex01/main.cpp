#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main()
{
    PhoneBook book;
    std::string command;

    std::cout << "Welcome to My Awesome PhoneBook!" << std::endl;
    while (true)
    {
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
