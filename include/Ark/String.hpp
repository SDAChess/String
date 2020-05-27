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
#include <cstdio>    // for std::snprintf
#include <utility>   // for std::forward

/**
 * @brief A simple string class, smaller and faster compared to std::string
 * 
 */
class String
{
public:
    /**
     * @brief Construct a new String object
     * 
     */
    String();

    /**
     * @brief Construct a new String object
     * 
     * @param cString 
     */
    String(const char* cString);

    /**
     * @brief Construct a new String object
     * 
     * @param string 
     */
    String(const String& string);

    /**
     * @brief Destroy the String object
     * 
     */
    ~String();

    /**
     * @brief Return the size of the string (not counting the \0 at the end)
     * 
     * @return unsigned 
     */
    unsigned size() const;

    /**
     * @brief A pointer to the internal char*
     * 
     * @return const char* 
     */
    const char* c_str() const;

    /**
     * @brief Compare this string with another one
     * 
     * @param other 
     * @return true If they are equal
     * @return false Otherwise
     */
    bool equals(const String& other) const;

    /**
     * @brief Compare this string with another one
     * 
     * @param other 
     * @return true If they are equal
     * @return false Otherwise
     */
    bool equals(const char* other) const;

    /**
     * @brief Return the index of a specific character. If not found, -1 is returned
     * 
     * @param c 
     * @return int -1 if not found, otherwise its position in the string is returned
     */
    int index(char c) const;

    /**
     * @brief Concat this string with another one. The instance is modified
     * 
     * @param string 
     * @return String& 
     */
    String& concat(const String& string);

    /**
     * @brief Concat this string with another one. The instance is modified
     * 
     * @param string 
     * @return String& 
     */
    String& concat(const char* string);

    /**
     * @brief Convert this string to upper case. The instance is modified
     * 
     * @return String& 
     */
    String& toUpper();

    /**
     * @brief Convert this string to lower case. The instance is modified
     * 
     * @return String& 
     */
    String& toLower();

    /**
     * @brief Find a substring in this string
     * 
     * @param string 
     * @return int the starting position of the substring is found, -1 otherwise
     */
    int find(String& string);

    /**
     * @brief Find a substring in this string
     * 
     * @param string 
     * @return int the starting position of the substring is found, -1 otherwise
     */
    int find(const char* cString);

    /**
     * @brief Replace `target` (if found) by `replacement in this string. The instance is modified
     * 
     * @param target 
     * @param replacement 
     * @return String& 
     */
    String& replace(String& target, String& replacement);

    /**
     * @brief Replace `target` (if found) by `replacement in this string. The instance is modified
     * 
     * @param target 
     * @param replacement 
     * @return String& 
     */
    String& replace(String& target, const char* replacement);

    /**
     * @brief Replace `target` (if found) by `replacement in this string. The instance is modified
     * 
     * @param target 
     * @param replacement 
     * @return String& 
     */
    String& replace(const char* target, String& replacement);

    /**
     * @brief Replace `target` (if found) by `replacement in this string. The instance is modified
     * 
     * @param target 
     * @param replacement 
     * @return String& 
     */
    String& replace(const char* target, const char* replacement);

    /**
     * @brief Erase characters from `from` to end if `to` is -1. Otherwise erase until `to` (character at `to` isn't erased). The instance is modified
     * 
     * @param from Starting position to erase from
     * @param to defaults to -1 (meaning: end of string)
     * @return String& 
     */
    String& erase(int from, int to=-1);

    /**
     * @brief Simplified version of erase. Starts at position 0 and stops at `to` (character at `to` is erased). The instance is modified
     * 
     * @param to 
     * @return String& 
     */
    String& erase_front(int to);

    /**
     * @brief Convert this string to an std::string object. Be careful since this operation is costly
     * 
     * @return std::string 
     */
    std::string toString() const;

    /**
     * @brief Copy another string
     * 
     * @param string 
     * @return String& 
     */
    String& operator=(const String& string);

    /**
     * @brief Get a character at a given index
     * 
     * @param index 
     * @return char 
     */
    char operator[](unsigned index) const;

    /**
     * @brief Get a character at a given index
     * 
     * @param index 
     * @return char 
     */
    char& operator[](unsigned index);

    /**
     * @brief Format a string using snprintf
     * 
     * @tparam Args 
     * @param n Maximum number of bytes to use
     * @param args Arguments to format
     * @return String& 
     */
    template<typename... Args>
    String& format(unsigned n, Args&&... args);

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
    unsigned m_size;
    char* m_buffer;
};

#include "String.inl"

#endif // ARKSCRIPT_STRING_H
