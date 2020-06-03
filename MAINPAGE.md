# String
A lightweight, dependency-free C++ custom string, with homemade formatting.

## Install

Using CMake:
* `add_subdirectory(String)`
* include files to add in your `include_directories(...)`: `STRING_INCLUDES`
* source files to add to your target: `STRING_SOURCES`

## How to use

~~~~{.cpp}
#include <Ark/String.hpp>
#include <iostream>  // for printing

String text("Hello, world!");
std::cout << text.c_str() << std::endl;
~~~~

## [Benchmark](http://quick-bench.com/DYwVJg3S2xX-WIz9ZZruTghxb5A)

## Details

Compiled with MSVC 15.9 (Win32)
* Debug mode: `sizeof(String)` = 8 bytes
* Release mode: `sizeof(String)` = 8 bytes
* all tests are passing

Compiled with MSVC 15.9 (64bits)
* Debug mode: `sizeof(String)` = 16 bytes
* Release mode: `sizeof(String)` = 16 bytes
* all tests are passing