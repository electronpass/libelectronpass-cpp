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

install(TARGETS electronpass LIBRARY DESTINATION "lib"
                      RUNTIME DESTINATION "bin"
                      ARCHIVE DESTINATION "lib"
                      COMPONENT library)

install(DIRECTORY ../include/ DESTINATION include/electronpass)
