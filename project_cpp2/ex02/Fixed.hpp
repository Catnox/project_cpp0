#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>
#include <cmath>

class Fixed
{
	private:
		int					_rawBits;
		static const int	_fractionalBits = 8;
	public:
		// Canonical form
		Fixed();
		Fixed(const Fixed &other);
		Fixed &operator=(const Fixed &other);
		~Fixed();
		// Additional constructors
		Fixed(const int intValue);
		Fixed(const float floatValue);
		// Conversion methods
		float toFloat() const;
		int toInt() const;
		// Getter and Setter
		int getRawBits( void ) const;
		void setRawBits( const int raw );
		// Arithmetic operators
		Fixed operator*(const Fixed &other) const;
		Fixed operator+(const Fixed &other) const;
		Fixed operator-(const Fixed &other) const;
		Fixed operator/(const Fixed &other) const;
		// Comparison operators
		bool operator>(const Fixed &other) const;
		bool operator<(const Fixed &other) const;
		bool operator>=(const Fixed &other) const;
		bool operator<=(const Fixed &other) const;
		bool operator==(const Fixed &other) const;
		bool operator!=(const Fixed &other) const;
		// Increment operators
		Fixed &operator++();       // Prefix
		Fixed operator++(int);     // Postfix
		// Decrement operators
		Fixed &operator--();       // Prefix
		Fixed operator--(int);     // Postfix
		// Static member functions
		static Fixed &max(Fixed &a, Fixed &b);
		static const Fixed &max(const Fixed &a, const Fixed &b);
		static Fixed &min(Fixed &a, Fixed &b);
		static const Fixed &min(const Fixed &a, const Fixed &b);
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif