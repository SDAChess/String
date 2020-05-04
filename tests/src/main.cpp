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

        return s == d;
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

    std::cout << "Tests passed: " << passed << "/" << total << std::endl;

    return 0;
}