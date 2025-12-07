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
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif