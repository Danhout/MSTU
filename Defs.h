#ifndef DEFINES_H_DDP
#define DEFINES_H_DDP
#include<cstring> // void * memcpy(void * src, void * dest, size_t size);

typedef unsigned long long size_t;

template<typename T>
void constructor(T & elem) { elem = 0; }
template<typename T>
void copy(T & elem, const T & other) { elem = other; }
template<typename T>
T && move(T & elem) { return (T &&) elem; }
template<typename T>
void constructor(T & elem, const T &  other) { constructor(elem); copy(elem, other); }
template<typename T>
void constructor(T & elem, const T && other) { elem = other; }
template<typename T>
void destructor(T & elem) {}
template<typename T>
void swap(T & first, T & second) { 
	T buff;
	memcpy(buff,   first, sizeof(T));
	memcpy(first, second, sizeof(T));
	memcpy(second,  buff, sizeof(T));
}

#endif //DEFINES_H_DDP