cmake_minimum_required(VERSION 2.8.7)
project(electronpass)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wold-style-cast -pedantic")

#find sodium lib either for android or normal builds
if(DEFINED ANDROID_ABI)
    set(SODIUM_PATH ${PROJECT_SOURCE_DIR}/../libsodium/libsodium-android-${ANDROID_ABI}/lib/libsodium.a)
    add_library(sodium STATIC IMPORTED)
    set_property(TARGET sodium PROPERTY IMPORTED_LOCATION ${SODIUM_PATH})
    include_directories(include jsoncpp ${PROJECT_SOURCE_DIR}/../libsodium/libsodium-android-${ANDROID_ABI}/include)
else()
    find_package(sodium REQUIRED)
    include_directories(include jsoncpp ${sodium_INCLUDE_DIR})
endif()

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)
add_subdirectory(examples EXCLUDE_FROM_ALL)

add_custom_target(docs COMMAND doxygen docs/Doxyfile WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(check
    COMMAND make tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests
)

install(DIRECTORY jsoncpp/ DESTINATION include/electronpass)#/usr/include/electronpass/)


add_custom_target(uninstall COMMAND xargs rm < install_manifest.txt)
