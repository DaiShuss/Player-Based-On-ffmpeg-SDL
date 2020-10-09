cmake_minimum_required(VERSION 3.16)
project(TrySDL)

set(SDL_DIR /usr/local/Cellar/sdl2/2.0.12_1)
set(FFMPEG_DIR /usr/local/Cellar/ffmpeg/4.3.1_1)

include_directories(
        ${FFMPEG_DIR}/include/
        ${SDL_DIR}/include/
)

link_directories(
        ${FFMPEG_DIR}/lib/
        ${SDL_DIR}/lib/
)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrySDL main.cpp)

target_link_libraries(
        TrySDL
        sdl2
        avcodec
        avformat
        swscale
)