#ifndef STRING_H_DDP
#define STRING_H_DDP
#include "Vector.h"
#include <cstring>
#include <iostream>


typedef Vector<char> String;


String & constructor(String & str) {
	constructor(str, 1, '\0');
	return str;
}
String & constructor(String & str, const char * cStr) {
	size_t lenCStr = strlen(cStr);
	constructor(str, lenCStr + 1);
	memcpy(str.data, cStr, lenCStr + 1);
	return str;
}

size_t len(const String & str) {
	return strlen(str.data);
}

String & sum(String & src, const char * dest, size_t lenDest) {
	if (src.capacity < src.size + lenDest)
		reserve(src, src.size + lenDest);
	memcpy(src.data + len(src), dest, lenDest + 1);
	src.size += lenDest;
	return src;
}
String & operator+=(String & src, const char * dest) {
	return sum( src, dest, strlen(dest) );
}
String & operator+=(String & src, const String & dest) {
	return sum( src, dest.data, len(dest) );
}
String & operator+=(String & src, String && dest) {
	sum( src, dest.data, len(dest) );
	destructor(dest);
	return src;
}

// the return values will be need destructured
String && sum(const char * cStr1, const char * cStr2, size_t lenStr1, size_t lenStr2) {
	String resStr;
	constructor(resStr);
	reserve(resStr, lenStr1 + lenStr2 + 1);
	sum(resStr, cStr1, lenStr1);
	sum(resStr, cStr2, lenStr2);
	return move(resStr);
}
String && operator+(const char * cStr1, const String & str2) {
	return sum( cStr1, str2.data, strlen(cStr1), len(str2) );
}
String && operator+(const char * cStr1, String && str2) {
	String resStr;
	constructor(resStr, cStr1 + str2);
	destructor(str2);
	return move(resStr);
}
String && operator+(const String & str1, const char * cStr2) {
	return sum( str1.data, cStr2, len(str1), strlen(cStr2) );
}
String && operator+(const String & str1, const String & str2) {
	return sum( str1.data, str2.data, len(str1), len(str2) );
}
String && operator+(const String & str1, String && str2) {
	String resStr;
	constructor(resStr, str1 + str2);
	destructor(str2);
	return move(resStr);
}
String && operator+(String && str1, const char * cStr2) {
	String resStr;
	constructor(resStr, str1 + cStr2);
	destructor(str1);
	return move(resStr);
}
String && operator+(String && str1, const String & str2) {
	String resStr;
	constructor(resStr, str1 + str2);
	destructor(str1);
	return move(resStr);
}
String && operator+(String && str1, String && str2) {
	String resStr;
	constructor(resStr, str1 + str2);
	destructor(str1);
	destructor(str2);
	return move(resStr);
}

std::istream & operator>>(std::istream & in, String & str) {
	destructor(str);
	constructor(str);
	for (char c = in.get(); isgraph(c); c = in.get()) {
		back(str) = c;
		pushBack(str, '\0');
	}
	return in;
}
std::ostream & operator<<(std::ostream & out, const String & str) {
	out << str.data;
	return out;
}

#endif //STRING_H_DDP