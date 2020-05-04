cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)

project(ArkScriptString)

set(STRING_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/String.cpp"

    PARENT_SCOPE
)

set(STRING_INCLUDES
    "${CMAKE_CURRENT_LIST_DIR}/include"

    PARENT_SCOPE
)