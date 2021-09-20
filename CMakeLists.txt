cmake_minimum_required(VERSION 3.10)

project(String)

add_subdirectory(src)

target_include_directories(ArkScriptString PUBLIC "include/Ark")

enable_testing ()
add_subdirectory (tests)
