#ifndef MSTU_22KIO083_NUMBER_H
#define MSTU_22KIO083_NUMBER_H
#include <vector>
#include <iostream>

namespace MSTU {
namespace id22kio083 {
	bool isDigit(char c);
	bool isLittleLetter(char c);
	bool isBigLetter(char c);
	bool isLetter(char c);
		
	int charToIntDigit(char c);
	int charToInt(char c);

	struct Number {
		Number();
		Number( const Number& number );
		Number( const std::string revInteger, unsigned base = 10 );
		Number( const std::vector<unsigned>& revInteger, unsigned base = 10 );
		Number( const Number& number, unsigned base );

		const std::vector<unsigned>& getInteger() const;
		unsigned getBase() const;
		unsigned operator[](int i) const;
	
		Number& operator+=(unsigned syll);
		Number& operator*=(unsigned mult);
	
		friend std::ostream& operator<<(std::ostream& out, const Number& number);
		friend std::istream& operator>>(std::istream& in, Number& number);

		static const unsigned NUMBER_BASE_MAX = 10000;

	private:
		std::vector<unsigned> _integer;
		unsigned _base;
	};

	std::string to_string(const Number& number);
}
}

#endif