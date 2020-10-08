cmake_minimum_required(VERSION 3.16)
project(TrySDL)

set(SDL_DIR /usr/local/Cellar/sdl2/2.0.12_1)
include_directories(${SDL_DIR}/include/)
link_directories(${SDL_DIR}/lib/)
set(CMAKE_CXX_STANDARD 14)

add_executable(TrySDL main.cpp)

target_link_libraries(
        TrySDL
        sdl2
)