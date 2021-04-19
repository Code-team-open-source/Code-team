cmake_minimum_required(VERSION 3.10)

project(Code-team)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -O0)
endif (MSVC)


add_executable(code-team src/main.cpp
                         src/Game.cpp
                         src/Tool.cpp
                         src/Player.cpp
                         src/Task.cpp
                         src/ServerConnection.cpp
        src/protocols.cpp src/protocols.h)
if(WIN32)
    target_link_libraries(code-team ws2_32)
endif()

