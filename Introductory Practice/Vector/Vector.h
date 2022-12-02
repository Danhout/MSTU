#ifndef VECTOR_H_DDP
#define VECTOR_H_DDP
#include "Defs.h"
#include "Math.h"


template<typename T>
struct Vector {
	T *    data;
	size_t capacity;
	size_t size;
};


// Member functions
template<typename T>
Vector<T> & constructor(Vector<T> & vector, size_t count = 0) {
	vector.data = new T[count];
	for (size_t i = 0; i < count ; ++i)
		constructor(vector.data[i]);
	vector.capacity = count;
	vector.size 	= count;
	return vector;
}
template<typename T>
Vector<T> & constructor(Vector<T> & vector, const Vector<T> & other) {
	size_t count = other.size;
	vector.data = new T[count];
	for (size_t i = 0; i < count; ++i)
		constructor(vector.data[i], other.data[i]);
	vector.capacity = count;
	vector.size     = count;
	return vector;
}
template<typename T>
Vector<T> & constructor(Vector<T> & vector, Vector<T> && other) {
	vector.data		= other.data;
	vector.capacity = other.capacity;
	vector.size 	= other.size;
	return vector;
}
template<typename T>
Vector<T> & constructor(Vector<T> & vector, size_t count, const T & value) {
	vector.data = new T[count];
	for (size_t i = 0; i < count ; ++i)
		constructor(vector.data[i], value);
	vector.capacity = count;
	vector.size 	= count;
	return vector;
}
template<typename T>
Vector<T> & constructor(Vector<T> & vector, const T * first, const T * last) {
	size_t count = last - first;
	vector.data = new T[count];
	for (size_t i = 0; i < count ; ++i)
		constructor(vector.data[i], first[i]);
	vector.capacity = count;
	vector.size 	= count;
	return vector;
}
template<typename T>
void destructor(Vector<T> & vector) {
	for (size_t i = 0; i < vector.size; ++i)
		destructor(vector.data[i]);
	delete[] vector.data;
}

// Element access
template<typename T>
T & at(const Vector<T> & vector, size_t i) {
	if (i >= vector.size)
		throw "out of range";
	return vector.data[i];
}
template<typename T>
T & front(const Vector<T> & vector) { return at(vector, 0); }
template<typename T>
T &  back(const Vector<T> & vector) { return at(vector, vector.size - 1); }

// Iterators
template<typename T>
T * begin(const Vector<T> & vector) { return vector.data; }
template<typename T>
T *   end(const Vector<T> & vector) { return vector.data + vector.size; }
template<typename T>
const T * cbegin(const Vector<T> & vector) { return vector.data; }
template<typename T>
const T *   cend(const Vector<T> & vector) { return vector.data + vector.size; }

// Capacity
template<typename T>
bool empty(const Vector<T> & vector) { return vector.size == 0; }
template<typename T>
void reserve(Vector<T> & vector, size_t newCap) {
	if (vector.capacity == newCap)
		return;
	vector.capacity = newCap;
	for (size_t i = newCap; i < vector.size; ++i)
		destructor(vector.data[i]);
	vector.size = min(vector.size, newCap);
	T * buff = vector.data;
	vector.data = new T[newCap];
	memcpy(vector.data, buff, sizeof(T) * vector.size);
	delete[] buff;
}
template<typename T>
void shrinkToFit(Vector<T> & vector) { reserve(vector, vector.size); }

// Modifiers
template<typename T>
void clear(Vector<T> & vector) {
	for (size_t i = 0; i < vector.size; ++i)
		destructor(vector.data[i]);
	vector.size = 0;
}
template<typename T>
T * insert(Vector<T> & vector, const T * pos, const T & value, size_t count = 1) {
	if (pos < cbegin(vector) || cend(vector) < pos || count == 0)
		return nullptr;
	size_t newSize = vector.size + count;
	size_t iPos = pos - cbegin(vector);
	if (newSize > vector.capacity)
		reserve(vector, newSize * 3 / 2 + 1);
	for (size_t i = newSize - 1; i >= iPos + count; --i)
		constructor( vector.data[i], move(vector.data[i - count]) );
	for (size_t i = 0; i < count; ++i)
		constructor(vector.data[iPos + i], value);
	vector.size = newSize;
	return vector.data + iPos;
}
template<typename T>
T * insert(Vector<T> & vector, const T * pos, const T * first, const T * last) {
	if (pos < cbegin(vector) || cend(vector) < pos || last <= first)
		return nullptr;
	size_t count = last - first;
	T * buff = new T[count];
	for (size_t i = 0; i < count; ++i)
		constructor(buff[i], first[i]);
	size_t newSize = vector.size + count;
	size_t iPos = pos - cbegin(vector);
	if (newSize > vector.capacity)
		reserve(vector, newSize * 3 / 2 + 1);
	for (size_t i = newSize - 1; i >= iPos + count; --i)
		constructor( vector.data[i], move(vector.data[i - count]) );
	for (size_t i = 0; i < count; ++i)
		constructor( vector.data[iPos + i], move(buff[i]) );
	delete[] buff;
	vector.size = newSize;
	return vector.data + iPos;
}
template<typename T>
T * erase(Vector<T> & vector, const T * pos) {
	if (pos < cbegin(vector) || cend(vector) <= pos)
		return nullptr;
	size_t iPos = pos - cbegin(vector);
	destructor(vector.data[iPos]);
	for (size_t i = iPos + 1; i < vector.size; ++i)
		constructor( vector.data[i - 1], move(vector.data[i]) );
	vector.size -= 1;
	return vector.data + iPos;
}
template<typename T>
T * erase(Vector<T> & vector, const T * first, const T * last) {
	if (last <= first || first < cbegin(vector) || cend(vector)  < last)
		return nullptr;
	size_t count = last - first;
	size_t iPos = first - cbegin(vector);
	for (size_t i = 0; i < count; ++i)
		destructor(vector.data[iPos + i]);
	for (size_t i = iPos + count; i < vector.size; ++i)
		constructor( vector.data[i - count], move(vector.data[i]) );
	vector.size -= count;
	return vector.data + iPos;
}
template<typename T>
void pushBack(Vector<T> & vector, const T & elem) { insert(vector, cend(vector), elem); }
template<typename T>
void popBack(Vector<T> & vector) { erase(vector, cend(vector) - 1); }
template<typename T>
void resize(Vector<T> & vector, size_t count) {
	if (count > vector.capacity)
		reserve(vector, count * 3 / 2 + 1);
	for (size_t i = vector.size; i < count; ++i)
		constructor(vector.data[i]);
	for (size_t i = count; i < vector.size; ++i)
		destructor(vector.data[i]);
	vector.size = count;
}
template<typename T>
void swap(Vector<T> & vector, Vector<T> & other) {
	swap(vector.data,     other.data);
	swap(vector.capacity, other.capacity);
	swap(vector.size,     other.size);
}

// Member function(copy)
template<typename T>
Vector<T> copy(Vector<T> & vector, const Vector<T> & other) {
	if (vector == other)
		return vector;
	if (other.size > vector.capacity)
		reserve(vector, other.size);
	for (size_t i = other.size; i < vector.size; ++i)
		destructor(vector.data[i]);
	for (size_t i = vector.size; i < other.size; ++i)
		constructor(vector.data[i], other.data[i]);
	for (size_t i = 0, iMax = min(vector.size, other.size); i < iMax; ++i)
		copy(vector.data[i], other.data[i]);
	vector.size = other.size;
	return vector;
}

#endif //VECTOR_H_DDP