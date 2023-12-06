cmake_minimum_required(VERSION 3.25)
project(Letopiya)
set(CMAKE_EXE_LINKER_FLAGS "-static")
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)



set(CMAKE_CXX_STANDARD 17)

add_executable(Letopiya src/main.cpp src/button.cpp
        src/LGui.cpp
        src/headers.h
        )

target_link_libraries(Letopiya sfml-graphics)
