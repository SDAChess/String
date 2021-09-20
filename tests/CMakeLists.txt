include_directories (
    ${ArkScriptString_SOURCE_DIR}/src
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

add_test (NAME StringTests COMMAND tests)
