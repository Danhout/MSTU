#include <iostream>
#include <sstream>
#include <conio.h>
#include "Vector.h"
#include "String.h"

using namespace std;

template<typename T>
ostream & operator<<(ostream & out, const Vector<T> & vector);

int main() {
	cout << "Vector<int>:\n";
	Vector<int> vector;
	constructor(vector);

	pushBack(vector,  987654321);
	cout << vector << '\n';

	pushBack(vector, 1234567890);
	pushBack(vector, 2134567890);
	cout << vector << '\n';

	at(vector, 0) = 123456789;
	cout << vector << '\n';

	insert(vector, cbegin(vector) + 2, 1023456789, 2);
	cout << vector << '\n';

	erase(vector, cbegin(vector) + 1, cend(vector) - 1);
	cout << vector << "\n\n";
	destructor(vector);


	cout << "String:\n";
	String string;
	constructor(string);
	cout << '"' << string << "\" - len: " << len(string) << '\n';

	istringstream in("Hello, world");
	in >> string;
	cout << '"' << string << "\" - len: " << len(string) << '\n';

	in >> string;
	cout << '"' << string << "\" - len: " << len(string) << '\n';

	String string2;
	constructor(string2, "Hello, " + string + "!");
	cout << '"' << string2 << "\" - len: " << len(string2) << endl;

	destructor(string2);
	destructor(string);

	cout << "Нажмите любую клавишу для завершения..." << flush;
	getch();
	return 0;
}

template<typename T>
ostream & operator<<(ostream & out, const Vector<T> & vector) {
	if (vector.size == 0)
		return out << "[]";

	out << '[' << at(vector, 0);
	for (size_t i = 1; i < vector.size; ++i)
		out << ", " << at(vector, i);
	out << ']';
	return out;
}