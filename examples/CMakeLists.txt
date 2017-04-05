add_executable(passwords_example passwords_example.cpp)
target_link_libraries(passwords_example electronpass)

add_executable(crypto_example crypto_example.cpp)
target_link_libraries(crypto_example electronpass)

add_executable(serialization_example serialization_example.cpp)
target_link_libraries(serialization_example electronpass)

add_custom_target(examples DEPENDS
    passwords_example
    crypto_example
    serialization_example
)
