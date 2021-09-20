cmake_minimum_required(VERSION 3.8)

project(Tests CXX)

# submodules
add_subdirectory(${PROJECT_SOURCE_DIR}/../ String)

# code
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# including content of project
include_directories(${STRING_INCLUDES})

target_link_libraries(${PROJECT_NAME} ArkScriptString) 

# setting up project properties
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
