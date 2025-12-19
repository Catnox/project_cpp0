#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>

class ScalarConverter
{
	private:
		// Private constructor to prevent instantiation
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();

		// Type detection
		enum LiteralType
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			PSEUDO_LITERAL,
			INVALID
		};

		// Helper methods
		static LiteralType	detectType(const std::string& literal);
		static bool			isChar(const std::string& literal);
		static bool			isInt(const std::string& literal);
		static bool			isFloat(const std::string& literal);
		static bool			isDouble(const std::string& literal);
		static bool			isPseudoLiteral(const std::string& literal);

		// Conversion and display
		static void			convertFromChar(const std::string& literal);
		static void			convertFromInt(const std::string& literal);
		static void			convertFromFloat(const std::string& literal);
		static void			convertFromDouble(const std::string& literal);
		static void			convertPseudoLiteral(const std::string& literal);

		// Display helpers
		static void			displayChar(double value, bool impossible);
		static void			displayInt(double value, bool impossible);
		static void			displayFloat(double value, bool isPseudo);
		static void			displayDouble(double value, bool isPseudo);

	public:
		// Static conversion method
		static void			convert(const std::string& literal);
};

#endif
