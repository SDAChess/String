#ifndef string_tests_hpp
#define string_tests_hpp

// Check windows
#if _WIN32 || _WIN64
    #if _WIN64
        #define ENVIRONMENT64
    #else
        #define ENVIRONMENT32
    #endif
#endif

// Check GCC
#if __GNUC__
    #if __x86_64__ || __ppc64__
        #define ENVIRONMENT64
    #else
        #define ENVIRONMENT32
    #endif
#endif

#include <functional>
#include <Ark/String.hpp>

class Tests
{
public:
    Tests();
    void operator()(const char* name, std::function<bool()>&& func);
    void report();

private:
    int m_passed, m_total;
};

#endif