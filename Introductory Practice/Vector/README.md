# Ознакомительная практика
## Вариант № 9
## Реализации Vector и String

***Исходные коды программы***

[Vector.h](Vector.h)

[String.h](String.h)

**Исходники, на которых основан функционал**

[Defs.h](Defs.h)

[Math.h](Math.h)

**Тесты программы**

[test.cpp](test.cpp)

***Особые моменты программы***

- Структура [Vector](Vector.h) является шаблонной, как и функции, работающие с ней
```c++
template<typename T>
struct Vector {
  T *    data;
  size_t capacity;
  size_t size;
}
```

- Структура [String](String.h) является специализацией шаблонной струкуты [Vector](Vector.h)<char>, как и её конструктор по умолчанию
```c++
typedef Vector<char> String;
```

- Для структуры [String](String.h) перегружены операторы конкатенации и побитового сдвига
```c++
String & operator+=(String & src, const char * dest);
String & operator+=(String & src, const String & dest);
String & operator+=(String & src, String && dest);

String && operator+(const char *   cStr1, const String &  str2);
String && operator+(const char *   cStr1,       String && str2);
String && operator+(const String &  str1, const char *   cStr2);
String && operator+(const String &  str1, const String &  str2);
String && operator+(const String &  str1,       String && str2);
String && operator+(      String && str1, const char *   cStr2);
String && operator+(      String && str1, const String &  str2);
String && operator+(      String && str1,       String && str2);

std::istream & operator>>(std::istream &  in,       String & str);
std::ostream & operator<<(std::ostream & out, const String & str);
```
