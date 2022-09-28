#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "number.h"

using std::vector;
using std::cout;
using MSTU::id22kio083::Number;

std::string centerString(std::string str, unsigned width, bool isCenterToRight = true) {
	if (width <= str.size())
		return str;
	unsigned marginLeft = ( width - str.size() + (isCenterToRight ? 1 : 0) ) / 2;
	unsigned marginRigth = width - str.size() - marginLeft;
	return std::string(marginLeft, ' ') + str + std::string(marginRigth, ' ');
}

int main() {
	const std::string STR_DEC = "122 78 101 254 150 220 225 159 216 236",
		 			  STR_BIN = R"S(10010000101101111110000100111010
									00010000011100100100001110010111
									11110001001100100011110010001010
									00001000010001101100100100000001
									11011101101011001100111111111001
									11110111011000101010100111011110
									00001110000111011101001010110011
									11100110001110110100010100100010
									11111001010110010011000001000011
									11100110101011101000001100110100)S";
	std::istringstream inDec(STR_DEC), 
					   inBin(STR_BIN);
	vector< vector<Number> > decBinHexNumbers(3),
							 binDecHexNumbers(3);

	for (Number decNumber; inDec >> decNumber;) {
		decBinHexNumbers[0].push_back(decNumber);
		decBinHexNumbers[1].emplace_back(decNumber, 2);
		decBinHexNumbers[2].emplace_back(decNumber, 16);
	}
	for (std::string strBin; inBin >> strBin;) {
		binDecHexNumbers[0].emplace_back(strBin, 2);
		binDecHexNumbers[1].emplace_back(binDecHexNumbers[0].back(), 10);
		binDecHexNumbers[2].emplace_back(binDecHexNumbers[0].back(), 16);
	}

	for (auto& arrayNumbers: {decBinHexNumbers, binDecHexNumbers}) {
		unsigned maxStrSize = 0;
		vector<unsigned> maxSizesColumns( arrayNumbers.size(), 0 );
		for (int i = 0; i < arrayNumbers.size(); ++i)
			for (const Number& number : arrayNumbers[i])
				maxSizesColumns[i] = std::max( (size_t) maxSizesColumns[i], MSTU::id22kio083::to_string(number).size() );
		cout << '|';
		for (int i = 0; i < arrayNumbers.size(); ++i)
			cout << centerString(std::to_string( arrayNumbers.at(i).at(0).getBase() ), maxSizesColumns[i]) << '|';
		cout << "\r\n";
		for (int j = 0; j < arrayNumbers.at(0).size(); ++j) {
			cout << '|';
			for (int i = 0; i < maxSizesColumns.size(); ++i) {
				cout << std::setw(maxSizesColumns[i]) << MSTU::id22kio083::to_string(arrayNumbers[i][j]) << '|';
			}
			cout << "\r\n";
		}
		cout << "\r\n\r\n";
	}

	return 0;
}