add_subdirectory(googletest)
include_directories(googletest/googletest/include)

set(TEST_FILES
    base64_test.cpp
    crypto_test.cpp
    serialization_test.cpp
    passwords_test.cpp
    wallet_test.cpp
)

add_executable(tests ${SRC} ${TEST_FILES})
target_link_libraries(tests sodium gtest gtest_main)
