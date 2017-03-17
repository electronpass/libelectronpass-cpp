add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(serialization_test serialization_test.cpp)
target_link_libraries(serialization_test electronpass)

add_executable(passgenerator_test passwords_test.cpp)
target_link_libraries(passgenerator_test electronpass)

add_executable(crypto_test crypto_test.cpp)
target_link_libraries(crypto_test electronpass)


set(TEST_FILES base64_test.cpp)
add_executable(tests ${TEST_FILES})
target_link_libraries(tests electronpass gtest gtest_main)
