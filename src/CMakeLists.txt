set(SOURCE_FILES
        crypto.cpp
        serialization.cpp
        passgenerator.cpp)

add_library(electronpass SHARED ${SOURCE_FILES})
target_link_libraries(electronpass jsoncpp)
