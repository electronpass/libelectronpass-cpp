add_executable(passwords_example ${SRC} passwords_example.cpp)
target_link_libraries(passwords_example sodium)

add_executable(crypto_example ${SRC} crypto_example.cpp)
target_link_libraries(crypto_example sodium)

add_executable(serialization_example ${SRC} serialization_example.cpp)
target_link_libraries(serialization_example sodium)

add_custom_target(examples DEPENDS
    passwords_example
    crypto_example
    serialization_example
)
