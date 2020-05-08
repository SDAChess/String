# String
A lightweight, dependency-free C++ custom string.

[![language](https://img.shields.io/badge/language-c++-blue.svg)](https://isocpp.org)

## Install

Use cmake and `add_subdirectory(String)`, then the files to include are located in `STRING_INCLUDES`, the files to compile in `STRING_SOURCES`

## How to use

```c++
#include <Ark/String.hpp>

String text("Hello, world!");
```

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