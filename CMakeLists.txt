cmake_minimum_required(VERSION 3.12)

Include(FetchContent)

project(enigma C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall
    -Wno-format
    -Wno-unused-function
    -Wno-maybe-uninitialized
)

FILE(
    GLOB
    SOURCES
    src/character.cpp
    src/enigma.cpp
    src/main.cpp
    src/rotor.cpp
    src/reflector.cpp
    src/plugboard.cpp
)

FILE(
    GLOB
    TEST_SOURCES
    test/src/*.cpp
    src/character.cpp
    src/enigma.cpp
    src/rotor.cpp
    src/reflector.cpp
    src/plugboard.cpp
)

add_executable(enigma
    ${SOURCES}
)

target_include_directories(enigma
    PRIVATE
    include/
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(
    tests
    ${TEST_SOURCES})

target_include_directories(tests
    PRIVATE
    include/
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
