#include <iostream>
#include <Ark/String.hpp>
#include "tests.hpp"

int main(int argc, char** argv)
{
    Tests tests;

    tests("construction", [](){
        String s;
        return s.size() == 0;
    });

    tests("default init", [](){
        String s("hello");
        return s.size() == 5;
    });

    tests("copy cstr", [](){
        String s("hello");
        String d(s);

        return s == d && strcmp(s.c_str(), "hello") == 0;
    });

    tests("size", [](){
        String s("abcdefghijklmnopqrstuvwxyz0123456789");
        return s.size() == 36;
    });

    tests("content", [](){
        String s("hello");
        return strcmp(s.c_str(), "hello") == 0;
    });

    tests("comparison", [](){
        String s("hello");
        String d("hello");
        return s == d;
    });

    tests("unequality", [](){
        String s("hello");
        String d("world");
        return s != d;
    });

    tests("index", [](){
        String s("hello");
        return s.index('h') == 0 &&
               s.index('e') == 1 &&
               s.index('z') == -1;
    });

    tests("concatenation", [](){
        String s("hello");
        String d("world");

        return strcmp((s + " " + d).c_str(), "hello world") == 0 && s == "hello" && d == "world";
    });

    tests("to upper", [](){
        String s("hElLo WorLd!");
        return s.toUpper() == "HELLO WORLD!";
    });

    tests("to lower", [](){
        String s("hElLo WorLd!");
        return s.toLower() == "hello world!";
    });

    tests("find", [](){
        String s("abcdefghijklmnopqrstuvwxyz0123456789");
        return s.find("hello") == -1 &&
               s.find("abc") == 0 &&
               s.find("hijk") == 7 &&
               s.find("89ab") == -1;
    });

    tests("replace", [](){
        String s("hello wolf, how are you?");
        return s.replace("wolf", "world") == "hello world, how are you?" &&
               s.replace("you?", "the seas today") == "hello world, how are the seas today";
    });

    tests("erase", [](){
        String s("hello world");
        s.erase(s.size() - 1);
        return s == "hello worl" && s.size() == 10;
    });

    tests("erase_front", [](){
        String s("hello world");
        s.erase_front(3); // 0 to 3, included
        return s == "o world" && s.size() == 7;
    });

    tests("erase (range)", [](){
        String s("hello world");
        s.erase(1, 2);
        return s == "hllo world" && s.size() == 10;
    });

    tests("get char", [](){
        String s("hello world");
        return s[0] == 'h' &&
               s[1] == 'e' &&
               s[2] == 'l' &&
               s[3] == 'l' &&
               s[4] == 'o' &&
               s[5] == ' ' &&
               s[6] == 'w' &&
               s[7] == 'o' &&
               s[8] == 'r' &&
               s[9] == 'l' &&
               s[10] == 'd' &&
               s[11] == '\0';
    });

    tests("comparisons", [](){
        String s("abc"), d("def");
        return s < d && "aBc" < d;
    });

    tests.report();

    return 0;
}