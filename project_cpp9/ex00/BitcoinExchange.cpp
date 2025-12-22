#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

// Constructeur par défaut
BitcoinExchange::BitcoinExchange()
{
}

// Constructeur avec fichier de base de données
BitcoinExchange::BitcoinExchange(std::string const &databaseFile)
{
	loadDatabase(databaseFile);
}

// Constructeur de copie
BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) : _database(src._database)
{
}

// Opérateur d'assignation
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
		_database = rhs._database;
	return *this;
}

// Destructeur
BitcoinExchange::~BitcoinExchange()
{
}

// Supprimer les espaces au début et à la fin
std::string BitcoinExchange::trim(std::string const &str) const
{
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}

// Charger la base de données CSV
void BitcoinExchange::loadDatabase(std::string const &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw FileOpenException();

	std::string line;
	// Skip header
	if (!std::getline(file, line))
		throw InvalidDatabaseException();

	while (std::getline(file, line))
	{
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;

		std::string date = trim(line.substr(0, commaPos));
		std::string rateStr = trim(line.substr(commaPos + 1));

		char *endPtr;
		double rate = std::strtod(rateStr.c_str(), &endPtr);
		if (*endPtr == '\0' && !rateStr.empty())
			_database[date] = rate;
	}
	file.close();

	if (_database.empty())
		throw InvalidDatabaseException();
}

// Vérifier si une date est valide (format YYYY-MM-DD)
bool BitcoinExchange::isValidDate(std::string const &date) const
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	// Vérification des jours par mois
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	// Année bissextile
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1])
		return false;

	return true;
}

// Vérifier si une valeur est valide (0 à 1000)
bool BitcoinExchange::isValidValue(std::string const &value, double &result) const
{
	if (value.empty())
		return false;

	char *endPtr;
	result = std::strtod(value.c_str(), &endPtr);

	if (*endPtr != '\0')
		return false;

	return true;
}

// Obtenir le taux de change pour une date (ou la date inférieure la plus proche)
double BitcoinExchange::getExchangeRate(std::string const &date) const
{
	std::map<std::string, double>::const_iterator it = _database.find(date);
	if (it != _database.end())
		return it->second;

	// Trouver la date inférieure la plus proche
	it = _database.lower_bound(date);
	if (it == _database.begin())
		return -1; // Pas de date antérieure
	--it;
	return it->second;
}

// Traiter le fichier d'entrée
void BitcoinExchange::processInputFile(std::string const &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw FileOpenException();

	std::string line;
	bool firstLine = true;

	while (std::getline(file, line))
	{
		// Skip header
		if (firstLine)
		{
			firstLine = false;
			if (line.find("date") != std::string::npos)
				continue;
		}

		// Chercher le séparateur " | "
		size_t pipePos = line.find(" | ");
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pipePos));
		std::string valueStr = trim(line.substr(pipePos + 3));

		// Valider la date
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		// Valider et parser la valeur
		double value;
		if (!isValidValue(valueStr, value))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		// Vérifier les limites
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		// Obtenir le taux et calculer
		double rate = getExchangeRate(date);
		if (rate < 0)
		{
			std::cerr << "Error: date too early." << std::endl;
			continue;
		}

		double result = value * rate;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	file.close();
}

// Exceptions
const char *BitcoinExchange::FileOpenException::what() const throw()
{
	return "Error: could not open file.";
}

const char *BitcoinExchange::InvalidDatabaseException::what() const throw()
{
	return "Error: invalid database file.";
}
