#include "Fixed.hpp"


// Canonical form
Fixed::Fixed() : _rawBits(0) {}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other)
{
	if (this != &other)
	{
		this->_rawBits = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {}

// Additional constructors
Fixed::Fixed(const int intValue)
{
	_rawBits = intValue << _fractionalBits;
}

Fixed::Fixed(const float floatValue)
{
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

// Arithmetic operators
Fixed Fixed::operator*(const Fixed &other) const
{
	return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator+(const Fixed &other) const
{
	return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const
{
	return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const
{
	return Fixed(this->toFloat() / other.toFloat());
}

// Comparison operators
bool Fixed::operator>(const Fixed &other) const
{
	return this->_rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed &other) const
{
	return this->_rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed &other) const
{
	return this->_rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed &other) const
{
	return this->_rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed &other) const
{
	return this->_rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed &other) const
{
	return this->_rawBits != other._rawBits;
}
// Increment operators
Fixed &Fixed::operator++()       // Prefix
{
	this->_rawBits++;
	return *this;
}	

Fixed Fixed::operator++(int)     // Postfix
{
	Fixed temp(*this);
	this->_rawBits++;
	return temp;
}

// Decrement operators
Fixed &Fixed::operator--()       // Prefix
{
	this->_rawBits--;
	return *this;
}

Fixed Fixed::operator--(int)     // Postfix
{
	Fixed temp(*this);
	this->_rawBits--;
	return temp;
}

// Static member functions
Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b) ? a : b;
}	

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

