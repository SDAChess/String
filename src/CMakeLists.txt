set(SOURCE_FILES String.cpp)

# We declare the project as a static library.
add_library(ArkScriptString STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(
    ArkScriptString
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
