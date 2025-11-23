#include "Contact.hpp"

Contact::Contact()
{
    std::cout << "Constructor called" << std::endl;
}
  
Contact::~Contact()
{
    std::cout << "Destructor called" << std::endl;
}

static bool isDigits(const std::string &s)
{
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.size(); ++i)
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    return true;
}

static bool isLettersNoSpace(const std::string &s)
{
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.size(); ++i)
        if (!std::isalpha(static_cast<unsigned char>(s[i])))
            return false;
    return true;
}

static bool promptValidate(const std::string &prompt, std::string &out,
                     bool (*validator)(const std::string&), const std::string &errMsg)
{
    std::string line;
    while (true)
    {
        std::cout << prompt;
        if (!std::getline(std::cin, line))
        {
            return false;
        }
        if (line.empty())
        {
            std::cout << "No input\n";
            continue;
        }
        if (validator(line))
        {
            out = line;
            return true;
        }
        std::cout << errMsg << "\n";
    }
}

static bool notEmpty(const std::string &s)
{
    return !s.empty();
}

bool Contact::setInfo()
{
    if (!promptValidate("First name: ", _firstName, isLettersNoSpace,
                        "First name must contain only letters and no spaces."))
        return false;

    if (!promptValidate("Last name: ", _lastName, isLettersNoSpace,
                        "Last name must contain only letters and no spaces."))
        return false;

    if (!promptValidate("Nickname: ", _nickname, isLettersNoSpace,
                        "Nickname must contain only letters and no spaces."))
        return false;

    if (!promptValidate("Phone number: ", _phoneNumber, isDigits,
                        "Phone number must contain only digits."))
        return false;

    if (!promptValidate("Darkest secret: ", _darkestSecret, notEmpty,
                        "Darkest secret cannot be empty."))
        return false;

    return true;
}

static std::string truncate(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void Contact::displayShort(int index) const
{
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << truncate(_firstName) << "|"
              << std::setw(10) << truncate(_lastName) << "|"
              << std::setw(10) << truncate(_nickname) << std::endl;
}

void Contact::displayFull() const
{
    std::cout << "First name: " << _firstName << std::endl;
    std::cout << "Last name: " << _lastName << std::endl;
    std::cout << "Nickname: " << _nickname << std::endl;
    std::cout << "Phone number: " << _phoneNumber << std::endl;
    std::cout << "Darkest secret: " << _darkestSecret << std::endl;
}