#include "tests.hpp"

#include <iostream>
#include <iomanip>

Tests::Tests() :
    m_passed(0), m_total(0)
{}

void Tests::operator()(const char* name, std::function<bool()>&& func)
{
    m_total++;
    if (func())
    {
        m_passed++;
        std::cout << std::setw(20) << name << " test passed" << std::endl;
    }
    else
        std::cout << 'x ' << std::setw(20) << name << " test failed" << std::endl;
}

void Tests::report()
{
    std::cout << "\nTests passed: " << m_passed << "/" << m_total << std::endl;
#ifdef ENVIRONMENT32
    std::cout << "Built on 32bits platform" << std::endl;
#elif defined(ENVIRONMENT64)
    std::cout << "Built on 64bits platform" << std::endl;
#endif
    std::cout << "sizeof(String) = " << sizeof(String) << std::endl;
}