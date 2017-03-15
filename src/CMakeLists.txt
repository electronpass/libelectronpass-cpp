set(SOURCE_FILES
        jsoncpp.cpp
        crypto.cpp
        serialization.cpp
        passwords.cpp
        base64.cpp
    )

add_library(electronpass SHARED ${SOURCE_FILES})
target_link_libraries(electronpass crypto)
