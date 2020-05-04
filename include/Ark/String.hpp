/**
 * @file String.hpp
 * @author madureira, Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A lightwieght, dependency-free C++ custom string
 * @version 0.1
 * @date 2020-05-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef ARKSCRIPT_STRING_H
#define ARKSCRIPT_STRING_H

#include <string.h>  // for memmove, memset
#include <string>    // for conversions

class String
{
public:
    String();

    String(const char* cString);

    String(const String& string);

    ~String();

    int size() const;

    const char* c_str() const;

    bool equals(const String& other) const;

    bool equals(const char* other) const;

    int index(char c) const;

    String& concat(const String& string);

    String& concat(const char* string);

    String& toUpper();

    String& toLower();

    int find(String& string);

    int find(const char* cString);

    String& replace(String& target, String& replacement);

    String& replace(String& target, const char* replacement);

    String& replace(const char* target, String& replacement);

    String& replace(const char* target, const char* replacement);

    String& erase(int from);

    String& erase_front(int to);

    std::string toString() const;

    String& operator=(const String& string);

    char operator[](unsigned int index) const;

    char& operator[](unsigned int index);

    friend bool operator==(const String& left, const String& right);

    friend bool operator==(const String& left, const char* right);

    friend bool operator==(const char* left, const String& right);

    friend bool operator!=(const String& left, const String& right);

    friend bool operator!=(const String& left, const char* right);

    friend bool operator!=(const char* left, const String& right);

    friend bool operator<(const String& left, const String& right);

    friend bool operator<(const String& left, const char* right);

    friend bool operator<(const char* left, const String& right);

    friend String operator+(const String& left, const String& right);

    friend String operator+(const String& left, const char* right);

    friend String operator+(const char* left, const String& right);

    String& operator+=(const String& string);

private:
    unsigned int m_size;
    char* m_buffer;
};

#endif // ARKSCRIPT_STRING_H
