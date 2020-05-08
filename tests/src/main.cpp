#include <iostream>
#include <Ark/String.hpp>

int main(int argc, char** argv)
{
    int passed = 0;
    int total = 0;

    auto TEST = [&passed, &total](const char* name, auto&& func) -> void {
        total++;
        if (func())
        {
            passed++;
            std::cout << name << " test passed" << std::endl;
        }
        else
            std::cout << name << " test failed" << std::endl;
    };

    TEST("size", [](){
        String s("hello");
        return s.size() == 5;
    });

    TEST("content", [](){
        String s("hello");
        return strcmp(s.c_str(), "hello") == 0;
    });

    TEST("copy & equality", [](){
        String s("hello");
        String d(s);

        return s == d && strcmp(s.c_str(), "hello") == 0;
    });

    TEST("unequality", [](){
        String s("hello");
        String d("world");
        return s != d;
    });

    TEST("concatenation", [](){
        String s("hello");
        String d("world");

        return strcmp((s + " " + d).c_str(), "hello world") == 0 && s == "hello" && d == "world";
    });

    TEST("erase", [](){
        String s("hello world");
        s.erase(s.size() - 1);
        return s == "hello worl" && s.size() == 10;
    });

    TEST("erase_front", [](){
        String s("hello world");
        s.erase_front(3); // 0 to 3, included
        return s == "o world" && s.size() == 7;
    });

    TEST("erase (range)", [](){
        String s("hello world");
        s.erase(1, 2);
        return s == "hllo world" && s.size() == 10;
    });

    std::cout << "\nTests passed: " << passed << "/" << total << std::endl;
    std::cout << "sizeof(String) = " << sizeof(String) << std::endl;

    return 0;
}