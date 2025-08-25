/* #ifndef CONTACT_HPP
#define CONTACT_HPP
#include <string>

class Contact
{
	private :
		std::string	_firstName;
		std::string	_lastName;
		std::string	_nickname;
		std::string	_phoneNumber;
		std::string	_darkestSecret;
	public :
				Contact();
		const	std::string& getFirstName() const;
		const	std::string& getLastName() const;
		const	std::string& getNickname() const;
		const	std::string& getPhoneNumber() const;
		const	std::string& getDarkestSecret() const;
		void	fill();
		void	print() const;
};

#endif */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <string>
#include <iostream>

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    Contact();
    void setInfo();
    void displayShort(int index) const;
    void displayFull() const;
    bool isEmpty() const;
};

#endif
