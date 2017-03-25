add_subdirectory(googletest)
include_directories(googletest/googletest/include)

set(TEST_FILES
    base64_test.cpp
    crypto_test.cpp
    serialization_test.cpp
    passwords_test.cpp
)

add_executable(tests ${TEST_FILES})
target_link_libraries(tests electronpass gtest gtest_main)
