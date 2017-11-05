set(SRC
        ${PROJECT_SOURCE_DIR}/src/crypto.cpp
        ${PROJECT_SOURCE_DIR}/src/jsoncpp.cpp
        ${PROJECT_SOURCE_DIR}/src/passwords.cpp
        ${PROJECT_SOURCE_DIR}/src/serialization.cpp
        ${PROJECT_SOURCE_DIR}/src/wallet.cpp)

add_library(electronpass STATIC ${SRC})
target_link_libraries(electronpass ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)
