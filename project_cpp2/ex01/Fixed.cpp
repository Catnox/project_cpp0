#include "Fixed.hpp"

// Canonical form
Fixed::Fixed() : _rawBits(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		this->_rawBits = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// Additional constructors
Fixed::Fixed(const int intValue)
{
	std::cout << "Int constructor called" << std::endl;
	_rawBits = intValue << _fractionalBits;
}

Fixed::Fixed(const float floatValue)
{
	std::cout << "Float constructor called" << std::endl;
	_rawBits = static_cast<int>(roundf(floatValue * (1 << _fractionalBits)));
}

// Conversion methods
float Fixed::toFloat() const
{
	return static_cast<float>(_rawBits) / (1 << _fractionalBits);
}

int Fixed::toInt() const
{
	return _rawBits >> _fractionalBits;
}

// Getter and Setter
int Fixed::getRawBits( void ) const
{
	return _rawBits;
}

void Fixed::setRawBits( const int raw )
{
	_rawBits = raw;
}

// Output stream operator
std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}