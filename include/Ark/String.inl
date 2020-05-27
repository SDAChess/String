#include <tuple>        // std::tuple, std::make_tuple
#include <utility>      // std::forward
#include <type_traits>  // std::is_same, std::enable_if
#include <exception>    // std::exception

#include <iostream>  // TODO REMOVE ME

namespace internal
{
    struct FormatData
    {
        char* temp;
        unsigned tempSize;
        unsigned i;

        char* buffer;
        unsigned bufSize;

        char tok;
        bool avoid_format;
        unsigned pos;
        unsigned used;
    };

    inline long long int abs(long long int val)
    {
        return val < 0 ? -1 * val : val;
    }

    inline void printNum(FormatData& fdata, long long int value, int base)
    {
        // get number of digits
        long long int copy = abs(value);
        char digCount = -1;
        for (; copy > 0; ++digCount)
            copy /= base;
        // handle negative numbers
        if (value < 0)
        {
            // overflow guard
            if (fdata.pos < fdata.tempSize)
            {
                fdata.temp[fdata.pos] = '-';
                fdata.pos++;
            }
            value *= -1;
        }
        // overflow guard
        if (fdata.pos + digCount >= fdata.tempSize)
            return;
        fdata.pos += digCount;
        unsigned end = fdata.pos;
        // copy into string
        do
        {
            // avoid buffer overflow
            if (fdata.pos < fdata.tempSize)
            {
                fdata.temp[fdata.pos] = "0123456789abcdef"[value % base];
                fdata.pos--;
            }
            else  // in case of buffer overflow, no need to burn cpu cycles cutting the number into pieces
                break;
            value /= base;
        } while (value > 0);
        fdata.pos = end + 1;  // + 1 because end is pointing at the last character in the string, we want the one after this one
    }

    template<unsigned I=0, typename... Tp>
    typename std::enable_if<sizeof...(Tp) < I, void>::type format(FormatData& fdata, std::tuple<Tp...>& tp)
    {}

    template<unsigned I=0, typename... Tp>
    typename std::enable_if<I <= sizeof...(Tp), void>::type format(FormatData& fdata, std::tuple<Tp...>& tp)
    {
        if constexpr (I > 0)  // do the actual formatting
        {
            auto value = std::get<I - 1>(tp);
            using T = decltype(value);

            if constexpr (std::is_same<T, int>::value               ||
                          std::is_same<T, long int>::value          ||
                          std::is_same<T, long long>::value         ||
                          std::is_same<T, unsigned>::value          ||
                          std::is_same<T, unsigned long>::value     ||
                          std::is_same<T, unsigned long long>::value)
            {
                if (fdata.tok == '%')  // default base is 10
                    printNum(fdata, value, 10);
                else if (fdata.tok == 'x')  // hexa
                    printNum(fdata, value, 16);
                else
                    throw std::exception("Unknown base in format specifier for number");
            }
            else if constexpr (std::is_same<T, const char*>::value)
            {
                // check format specifier
                if (fdata.tok != '%')
                    throw std::exception("Unknown format specifier for const char*");

                // copy string and avoid buffer overflow
                for (unsigned i = 0; fdata.pos < fdata.tempSize && value[i] != '\0'; ++i)
                {
                    fdata.temp[fdata.pos] = value[i];
                    fdata.pos++;
                }
            }
            else if constexpr (std::is_same<T, std::string_view>::value)
            {
                // check format specifier
                if (fdata.tok != '%')
                    throw std::exception("Unknown format specifier for std::string_view");

                // copy string and avoid buffer overflow
                for (unsigned i = 0; fdata.pos < fdata.tempSize && i < value.size(); ++i)
                {
                    fdata.temp[fdata.pos] = value[i];
                    fdata.pos++;
                }
            }
            else if constexpr (std::is_same<T, char>::value)
            {
                // check format specifier
                if (fdata.tok != '%')
                    throw std::exception("Unknown format specifier for char");

                // avoid buffer overflow
                if (fdata.pos < fdata.tempSize)
                {
                    fdata.temp[fdata.pos] = value;
                    fdata.pos++;
                }
            }

            // reset token to be ready to get another one
            fdata.tok = '\0';
            // copy the character we were on in the buffer
            fdata.i++;
            fdata.temp[fdata.pos] = fdata.buffer[fdata.i];
            fdata.i++;
            fdata.pos++;

            // increment '%%' used counter
            fdata.used++;

            if (fdata.used == sizeof...(Tp))
                fdata.avoid_format = true;
        }
        // otherwise iterate on the string
        for (; fdata.i < fdata.bufSize; ++fdata.i)
        {
            if (fdata.avoid_format)
            {
                fdata.temp[fdata.pos] = fdata.buffer[fdata.i];
                fdata.pos++;
            }
            else
            {
                if (fdata.tok != '%')
                {
                    // char - char
                    if (fdata.buffer[fdata.i] != '%')
                    {
                        fdata.temp[fdata.pos] = fdata.buffer[fdata.i];
                        fdata.pos++;
                    }
                    // char - %
                    else
                        fdata.tok = '%';
                }
                else
                {
                    fdata.tok = fdata.buffer[fdata.i];
                    // % - [special character to indicate a format]
                    if (fdata.buffer[fdata.i] == '%' || fdata.buffer[fdata.i] == 'x')
                        format<I + 1, Tp...>(fdata, tp);
                    // % - char
                    else
                        fdata.temp[fdata.pos] = '%';
                }
            }
        }
    }
}

template<typename... Args>
String& String::format(unsigned n, Args&&... args)
{
    std::tuple<Args...> parsed = std::make_tuple<Args...>(std::forward<Args>(args)...);

    internal::FormatData fdata;
    fdata.temp = new char[n];

    // 0-init the temp string
    {
        for (unsigned i = 0; i < n; ++i)
            fdata.temp[i] = '\0';
    }

    fdata.tempSize = n;
    fdata.buffer = m_buffer;
    fdata.bufSize = m_size;
    fdata.i = 0;
    fdata.tok = '\0';
    fdata.avoid_format = false;
    fdata.pos = 0;
    fdata.used = 0;

    internal::format(fdata, parsed);

    // copy the string back into the internal buffer
    // first, get its size
    unsigned i = 0;
    while (fdata.temp[i] != '\0')
        i++;
    m_size = i;
    // remove the old buffer
    delete[] m_buffer;
    // replace it with the new one
    m_buffer = fdata.temp;

    return *this;
}