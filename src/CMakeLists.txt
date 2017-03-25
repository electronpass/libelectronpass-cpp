set(SOURCE_FILES
        jsoncpp.cpp
        crypto.cpp
        serialization.cpp
        passwords.cpp
        base64.cpp
        wallet.cpp
    )

add_library(electronpass SHARED ${SOURCE_FILES})
target_link_libraries(electronpass sodium)

install(TARGETS electronpass DESTINATION /usr/lib)
install(DIRECTORY ../include/ DESTINATION /usr/include/electronpass)
