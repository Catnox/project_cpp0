#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_database;

	// Méthodes privées
	void		loadDatabase(std::string const &filename);
	bool		isValidDate(std::string const &date) const;
	bool		isValidValue(std::string const &value, double &result) const;
	double		getExchangeRate(std::string const &date) const;
	std::string	trim(std::string const &str) const;

public:
	// Constructeurs et destructeur
	BitcoinExchange();
	BitcoinExchange(std::string const &databaseFile);
	BitcoinExchange(BitcoinExchange const &src);
	BitcoinExchange &operator=(BitcoinExchange const &rhs);
	~BitcoinExchange();

	// Méthode principale
	void processInputFile(std::string const &filename);

	// Exceptions
	class FileOpenException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class InvalidDatabaseException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
