include_directories (
    ${String_SOURCE_DIR}/include/Ark
    "src/"
)

add_executable (tests
    src/tests.cpp
    src/main.cpp
)

target_link_libraries (
    tests
    ArkScriptString
)

set_target_properties(
    tests 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

add_test (NAME StringTests COMMAND tests)
