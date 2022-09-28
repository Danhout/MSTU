#include "number.h"
#include <stdexcept>
#include <vector>


namespace MSTU { namespace id22kio083 {


bool isDigit(char c) { return '0' <= c && c <= '9'; }
bool isLittleLetter(char c) { return ('a' <= c && c <= 'z'); }
bool isBigLetter(char c) { return ('A' <= c && c <= 'Z'); }
bool isLetter(char c) {	return isLittleLetter(c) || isBigLetter(c); }
		
int charToIntDigit(char c) {
	if ( !isDigit(c) ) throw std::invalid_argument("The character can be only digit");
	return c - '0';
}
int charToInt(char c) { 
	if ( isDigit(c) ) return charToIntDigit(c);
	if ( isLittleLetter(c) ) return (c - 'a');
	if ( isBigLetter(c) ) return (c - 'A');
	throw std::invalid_argument("The character can be only digit or letter");
	}


Number::Number() : _integer(1, 0), _base(10) {}
Number::Number(const Number& number) : _integer( number.getInteger() ), _base( number.getBase() ) {}
Number::Number(const std::string revInteger, unsigned base) : _integer( std::vector<unsigned>( revInteger.crbegin(), revInteger.crend() ) ), _base(base) {
	for (unsigned& digit : _integer)
		digit -= '0';
	if (_base < 2 || _base > 10)
		throw std::invalid_argument("The \" unsigned base \" argument can't be less than 2 or more than 10");
	for (unsigned i : _integer) 
		if (i >= base) 
			throw std::invalid_argument("Digit can't be equals or more than base of number system");
	if ( _integer.empty() ) 
		_integer.push_back(0);
}
Number::Number(const std::vector<unsigned>&	revInteger, unsigned base) : _integer( revInteger.crbegin(), revInteger.crend() ), _base(base) {
	if (_base < 2 || _base > NUMBER_BASE_MAX) 
		throw std::invalid_argument("The \" unsigned base \" argument can't be less than 2 or more than NUMBER_BASE_MAX");
	for (unsigned i : _integer) 
		if (i >= base) 
			throw std::invalid_argument("Digit can't be equals or more than base of number system");
	if ( _integer.empty() ) 
		_integer.push_back(0);
}
Number::Number(const Number& number, unsigned  base) : _integer(1, 0), _base(base) {
	if (_base < 2 || _base > NUMBER_BASE_MAX) 
		throw std::invalid_argument("The \" unsigned base \" argument can't be less than 2 or more than NUMBER_BASE_MAX");
	for (auto it_digit  = number.getInteger().crbegin(); it_digit != number.getInteger().crend(); ++it_digit) {
		*this *= number.getBase();
		*this += *it_digit;
	}
}

const std::vector<unsigned>& Number::getInteger() const { 
	return _integer; 
}
unsigned Number::getBase() const { 
	return _base;
}
unsigned Number::operator[](int i) const { 
	return _integer.at(i);
}

Number& Number::operator+=(unsigned syll) {
	unsigned buf = syll;
	for (unsigned& rDigit : _integer) {
		rDigit += buf;
		buf = rDigit / _base;
		rDigit %= _base;
	}
	while (buf != 0) {
		_integer.push_back(buf % _base);
		buf /= _base;
	}
	return *this;
}
Number& Number::operator*=(unsigned mult) {
	if(mult > NUMBER_BASE_MAX) throw std::invalid_argument("The multiplier argument \" int mult \" can't be more than NUMBER_BASE_MAX");
	unsigned buf = 0;
	for (unsigned& rDigit : _integer) { 
		rDigit = rDigit * mult + buf;
		buf = rDigit / _base;
		rDigit %= _base;
	}
	while (buf != 0) {
		_integer.push_back(buf % _base);
		buf /= _base;
	}
	return *this;
}

std::istream& operator>>(std::istream& in, Number& number) {
	std::string str;
	in >> str;

	std::vector<unsigned> digits( str.size() );

	for (size_t i = 0; i < str.size(); ++i)
		digits[i] = charToIntDigit(str[i]);
	number = Number(digits);
	return in;
}
std::ostream& operator<<(std::ostream& out, const Number& number) {
	out << to_string(number);
	return out;
}

std::string to_string(const Number& number) {
	std::string strNumber;
	if (number.getBase() < 11) 
		for ( int i = number.getInteger().size() - 1; i >= 0; --i ) 
			strNumber.push_back( char('0' + number[i]) );
	else if (number.getBase() < 38) 
		for ( int i = number.getInteger().size() - 1; i >= 0; --i ) 
			strNumber.push_back( number[i] < 10 ? char('0' + number[i]) : char('A' + number[i] - 10) );
	else 
		for ( int i = number.getInteger().size() - 1; i >= 0; --i ) 
			strNumber.append(std::to_string(number[i]) + " "); 
	return strNumber;
}


}}