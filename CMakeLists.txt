cmake_minimum_required(VERSION 2.8.7)
project(electronpass)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wold-style-cast -pedantic")

find_package(sodium REQUIRED)
include_directories(include jsoncpp ${sodium_INCLUDE_DIR})

set(SRC
        ${PROJECT_SOURCE_DIR}/src/base64.cpp
        ${PROJECT_SOURCE_DIR}/src/crypto.cpp
        ${PROJECT_SOURCE_DIR}/src/jsoncpp.cpp
        ${PROJECT_SOURCE_DIR}/src/passwords.cpp
        ${PROJECT_SOURCE_DIR}/src/serialization.cpp
        ${PROJECT_SOURCE_DIR}/src/wallet.cpp)

add_subdirectory(test)
add_subdirectory(examples)

add_custom_target(docs COMMAND doxygen docs/Doxyfile WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(check
    COMMAND make tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests
)
