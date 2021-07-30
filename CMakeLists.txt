cmake_minimum_required(VERSION 3.10)

project(ArkScriptString)

set(SOURCE_FILES "src/String.cpp")

# We declare the project as a static library and add all the source code files to it.
add_library(ArkScriptString STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(ArkScriptString PUBLIC "include")

set_target_properties(
    ArkScriptString
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
