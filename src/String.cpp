#include "String.hpp"

String::String()
{
    m_size = 0;
    m_buffer = new char[0];
}

String::String(const char* cString)
{
    if (cString)
    {
        unsigned n = 0;
        // get size
        while (cString[n] != '\0')
            n++;
        // copy
        m_buffer = new char[n + 1];
        for (unsigned i = 0; i < n; i++)
            m_buffer[i] = cString[i];
        m_buffer[n] = '\0';

        m_size = n;
    }
    else
    {
        m_size = 0;
        m_buffer = new char[0];
    }
}

String::String(const String& string)
{
    unsigned len = string.size();
    // copy string
    m_buffer = new char[len + 1];
    for (unsigned i = 0; i < len; i++)
        m_buffer[i] = string[i];

    m_size = len;
    m_buffer[len] = '\0';
}

String::~String()
{
    if (m_buffer != nullptr)
    {
        m_size = 0;
        delete[] m_buffer;
    }
}

unsigned String::size() const
{
    return m_size;
}

const char* String::c_str() const
{
    return m_buffer;
}

bool String::equals(const String& other) const
{
    if (m_size != other.size())
        return false;

    unsigned n = 0;
    while ((n < m_size) && (m_buffer[n] == other[n]))
        n++;
    return n == m_size;
}

bool String::equals(const char* other) const
{
    String string(other);
    return this->equals(string);
}

int String::index(char c) const
{
    for (unsigned i = 0; i < m_size; i++)
        if (m_buffer[i] == c)
            return static_cast<int>(i);
    return -1;
}

String& String::concat(const String& string)
{
    unsigned stringSize = string.size();
    unsigned newLength = m_size + stringSize;
    char* tempStr = new char[newLength + 1];

    // copy first string into the new buffer
    // then the other string
    unsigned i = 0;
    for (; i < m_size; i++)
        tempStr[i] = m_buffer[i];
    for (; i - m_size < stringSize; i++)
        tempStr[i] = string[i - m_size];

    delete[] m_buffer;
    m_buffer = tempStr;
    m_buffer[newLength] = '\0';
    m_size = newLength;

    return *this;
}

String& String::concat(const char* string)
{
    String other(string);
    return this->concat(other);
}

String& String::toUpper()
{
    char diff = ('a' - 'A');
    for (unsigned i = 0; i < m_size; i++)
    {
        if ('a' <= m_buffer[i] && m_buffer[i] <= 'z')
            m_buffer[i] -= diff;
    }
    return *this;
}

String& String::toLower()
{
    char diff = ('a' - 'A');
    for (unsigned i = 0; i < m_size; i++)
    {
        if ('A' <= m_buffer[i] && m_buffer[i] <= 'Z')
            m_buffer[i] += diff;
    }
    return *this;
}

int String::find(String& string)
{
    unsigned strSize = string.size();

    if (strSize == 0)
        return -1;

    int len = strSize - 1;
    int posSearch = 0;
    for (unsigned i = 0; i < m_size; ++i)
    {
        if (m_buffer[i] == string.c_str()[posSearch])
        {
            ++posSearch;
            if (posSearch == strSize)
                return i - len;
        }
        else
        {
            i -= posSearch;
            posSearch = 0;
        }
    }

    return -1;
}

int String::find(const char* cString)
{
    String string(cString);
    return this->find(string);
}

String& String::replace(String& target, String& replacement)
{
    int startAt = this->find(target);

    if (startAt == -1)
        return *this;

    int replacementSize = replacement.size();
    int targetSize = target.size();
    int newLength = m_size + replacementSize - targetSize;
    int len = newLength + 1;
    char* tempStr = new char[len];
    int intervalIndex = 0;

    if (replacementSize > 0)
    {
        for (int i = 0; i < newLength; i++)
        {
            if (i >= startAt && intervalIndex < replacementSize)
            {
                tempStr[i] = replacement[intervalIndex];
                intervalIndex++;
            }
            else
                tempStr[i] = m_buffer[intervalIndex > 0 ? (i + targetSize - intervalIndex) : i];
        }
    }
    else
    {
        for (int i = 0; i < newLength; i++)
        {
            if (i >= startAt && intervalIndex < targetSize)
            {
                tempStr[i] = m_buffer[i + targetSize];
                intervalIndex++;
            }
            else
                tempStr[i] = m_buffer[intervalIndex > 0 ? (i + targetSize) : i];
        }
    }

    delete[] m_buffer;
    m_size = newLength;
    m_buffer = tempStr;

    return *this;
}

String& String::replace(String& target, const char* replacement)
{
    String strReplacement(replacement);
    return this->replace(target, strReplacement);
}

String& String::replace(const char* target, String& replacement)
{
    String strTarget(target);
    return this->replace(strTarget, replacement);
}

String& String::replace(const char* target, const char* replacement)
{
    String strTarget(target);
    String strReplacement(replacement);
    return this->replace(strTarget, strReplacement);
}

String& String::erase(int from, int to)
{
    if (from < 0 || from > static_cast<int>(m_size))
        return *this;

    to = (to == -1) ? m_size : to;
    if (to == m_size)
        memset(&m_buffer[from], 0, to - from);
    else
        memmove(&m_buffer[from], &m_buffer[to], m_size - to);
    m_size -= to - from;
    return *this;
}

String& String::erase_front(int to)
{
    if (to < 0 || to > static_cast<int>(m_size))
        return *this;

    memmove(&m_buffer[0], &m_buffer[to + 1], m_size - to);
    m_size -= to + 1;
    return *this;
}

std::string String::toString() const
{
    return std::string(m_buffer);
}

String& String::operator=(const String& string)
{
    if (this == &string) return *this;

    int len = string.size();
    delete[] m_buffer;
    m_buffer = new char[len + 1];

    for (int i = 0; i < len; i++)
        m_buffer[i] = string[i];

    m_size = len;
    m_buffer[len] = '\0';

    return *this;
}

char String::operator[](unsigned index) const
{
    return m_buffer[index];
}

char& String::operator[](unsigned index)
{
    return m_buffer[index];
}

bool operator==(const String& left, const String& right)
{
    return left.equals(right);
}

bool operator==(const String& left, const char* right)
{
    return left.equals(right);
}

bool operator==(const char* left, const String& right)
{
    return right.equals(left);
}

bool operator!=(const String& left, const String& right)
{
    return !left.equals(right);
}

bool operator!=(const String& left, const char* right)
{
    return !left.equals(right);
}

bool operator!=(const char* left, const String& right)
{
    return !right.equals(left);
}

bool operator<(const String& left, const String& right)
{
    return strcmp(left.c_str(), right.c_str()) < 0;
}

bool operator<(const String& left, const char* right)
{
    return strcmp(left.c_str(), right) < 0;
}

bool operator<(const char* left, const String& right)
{
    return strcmp(left, right.c_str()) < 0;
}

String operator+(const String& left, const String& right)
{
    return String(left).concat(right);
}

String operator+(const String& left, const char* right)
{
    return String(left).concat(right);
}

String operator+(const char* left, const String& right)
{
    return String(left).concat(right);
}

String& String::operator+=(const String& string)
{
    return this->concat(string);
}
