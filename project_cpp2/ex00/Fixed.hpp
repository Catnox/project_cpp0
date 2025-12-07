#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>

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
		// Getter and Setter
		int getRawBits( void ) const;
		void setRawBits( const int raw );
};

#endif