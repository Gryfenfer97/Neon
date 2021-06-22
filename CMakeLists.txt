cmake_minimum_required(VERSION 3.8)

project(Neon)

file(GLOB_RECURSE SRC
    ${Neon_SOURCE_DIR}/src/*.cpp
    ${Neon_SOURCE_DIR}/main.cpp
)

add_executable(Neon ${SRC})

target_include_directories(Neon
    PUBLIC
        ${Neon_SOURCE_DIR}/include
)

set_target_properties(
        Neon
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
    )
