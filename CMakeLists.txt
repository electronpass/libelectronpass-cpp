cmake_minimum_required(VERSION 2.8.7)
project(electronpass)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wold-style-cast -pedantic")

find_package(sodium REQUIRED)
include_directories(include jsoncpp ${sodium_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)
add_subdirectory(examples EXCLUDE_FROM_ALL)

add_custom_target(docs COMMAND doxygen docs/Doxyfile WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

install(DIRECTORY jsoncpp/ DESTINATION include/electronpass)#/usr/include/electronpass/)
