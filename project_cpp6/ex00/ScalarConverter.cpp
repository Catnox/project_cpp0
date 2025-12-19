#include "ScalarConverter.hpp"

// Private constructors and destructor (not used)
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// ============================================================================
// TYPE DETECTION
// ============================================================================

bool ScalarConverter::isChar(const std::string& literal)
{
	// Format: 'c' (single character in quotes)
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return true;
	// Single printable character (not a digit)
	if (literal.length() == 1 && !std::isdigit(literal[0]) && std::isprint(literal[0]))
		return true;
	return false;
}

bool ScalarConverter::isInt(const std::string& literal)
{
	if (literal.empty())
		return false;
	
	size_t i = 0;
	if (literal[0] == '-' || literal[0] == '+')
	{
		if (literal.length() == 1)
			return false;
		i = 1;
	}
	
	for (; i < literal.length(); i++)
	{
		if (!std::isdigit(literal[i]))
			return false;
	}
	return true;
}

bool ScalarConverter::isFloat(const std::string& literal)
{
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return false;
	
	std::string withoutF = literal.substr(0, literal.length() - 1);
	
	if (withoutF.empty())
		return false;
	
	size_t i = 0;
	if (withoutF[0] == '-' || withoutF[0] == '+')
	{
		if (withoutF.length() == 1)
			return false;
		i = 1;
	}
	
	bool hasDecimal = false;
	bool hasDigit = false;
	
	for (; i < withoutF.length(); i++)
	{
		if (withoutF[i] == '.')
		{
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (std::isdigit(withoutF[i]))
		{
			hasDigit = true;
		}
		else
		{
			return false;
		}
	}
	
	return hasDecimal && hasDigit;
}

bool ScalarConverter::isDouble(const std::string& literal)
{
	if (literal.empty())
		return false;
	
	size_t i = 0;
	if (literal[0] == '-' || literal[0] == '+')
	{
		if (literal.length() == 1)
			return false;
		i = 1;
	}
	
	bool hasDecimal = false;
	bool hasDigit = false;
	
	for (; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (std::isdigit(literal[i]))
		{
			hasDigit = true;
		}
		else
		{
			return false;
		}
	}
	
	return hasDecimal && hasDigit;
}

bool ScalarConverter::isPseudoLiteral(const std::string& literal)
{
	return (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
			literal == "-inf" || literal == "+inf" || literal == "nan" ||
			literal == "inff" || literal == "inf");
}

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string& literal)
{
	if (isPseudoLiteral(literal))
		return PSEUDO_LITERAL;
	if (isChar(literal))
		return CHAR;
	if (isInt(literal))
		return INT;
	if (isFloat(literal))
		return FLOAT;
	if (isDouble(literal))
		return DOUBLE;
	return INVALID;
}

// ============================================================================
// DISPLAY HELPERS
// ============================================================================

void ScalarConverter::displayChar(double value, bool impossible)
{
	std::cout << "char: ";
	if (impossible || std::isnan(value) || std::isinf(value) ||
		value < 0 || value > 127)
	{
		std::cout << "impossible" << std::endl;
	}
	else if (!std::isprint(static_cast<int>(value)))
	{
		std::cout << "Non displayable" << std::endl;
	}
	else
	{
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
	}
}

void ScalarConverter::displayInt(double value, bool impossible)
{
	std::cout << "int: ";
	if (impossible || std::isnan(value) || std::isinf(value) ||
		value < static_cast<double>(std::numeric_limits<int>::min()) ||
		value > static_cast<double>(std::numeric_limits<int>::max()))
	{
		std::cout << "impossible" << std::endl;
	}
	else
	{
		std::cout << static_cast<int>(value) << std::endl;
	}
}

void ScalarConverter::displayFloat(double value, bool isPseudo)
{
	std::cout << "float: ";
	float f = static_cast<float>(value);
	
	if (std::isnan(f))
		std::cout << "nanf" << std::endl;
	else if (std::isinf(f))
		std::cout << (f > 0 ? "+inff" : "-inff") << std::endl;
	else
	{
		std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	}
	(void)isPseudo;
}

void ScalarConverter::displayDouble(double value, bool isPseudo)
{
	std::cout << "double: ";
	
	if (std::isnan(value))
		std::cout << "nan" << std::endl;
	else if (std::isinf(value))
		std::cout << (value > 0 ? "+inf" : "-inf") << std::endl;
	else
	{
		std::cout << std::fixed << std::setprecision(1) << value << std::endl;
	}
	(void)isPseudo;
}

// ============================================================================
// CONVERSION METHODS
// ============================================================================

void ScalarConverter::convertFromChar(const std::string& literal)
{
	char c;
	if (literal.length() == 3)
		c = literal[1];
	else
		c = literal[0];
	
	double value = static_cast<double>(c);
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertFromInt(const std::string& literal)
{
	long long ll = std::atoll(literal.c_str());
	bool overflow = (ll < std::numeric_limits<int>::min() || 
					 ll > std::numeric_limits<int>::max());
	
	double value = static_cast<double>(ll);
	
	displayChar(value, overflow);
	displayInt(value, overflow);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertFromFloat(const std::string& literal)
{
	float f = std::strtof(literal.c_str(), NULL);
	double value = static_cast<double>(f);
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertFromDouble(const std::string& literal)
{
	double value = std::strtod(literal.c_str(), NULL);
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertPseudoLiteral(const std::string& literal)
{
	double value;
	
	if (literal == "nan" || literal == "nanf")
		value = std::numeric_limits<double>::quiet_NaN();
	else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff")
		value = std::numeric_limits<double>::infinity();
	else
		value = -std::numeric_limits<double>::infinity();
	
	displayChar(value, true);
	displayInt(value, true);
	displayFloat(value, true);
	displayDouble(value, true);
}

// ============================================================================
// MAIN CONVERT METHOD
// ============================================================================

void ScalarConverter::convert(const std::string& literal)
{
	LiteralType type = detectType(literal);
	
	switch (type)
	{
		case CHAR:
			convertFromChar(literal);
			break;
		case INT:
			convertFromInt(literal);
			break;
		case FLOAT:
			convertFromFloat(literal);
			break;
		case DOUBLE:
			convertFromDouble(literal);
			break;
		case PSEUDO_LITERAL:
			convertPseudoLiteral(literal);
			break;
		case INVALID:
		default:
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			break;
	}
}
