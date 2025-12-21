cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_COMPILER g++)
project(tiny-ui VERSION 1.2.1 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    /usr/include/SDL2
    ${SDL2_TTF_INCLUDE_DIRS}
    /usr/include/SDL2_ttf      
)

add_executable(tiny-ui
    src/tiny_ui.cpp
    src/tiny_handler.cpp
    src/tiny_interface.cpp
    src/tiny_vector.cpp
)

target_link_libraries(tiny-ui
    ${SDL2_LIBRARIES}
    SDL2_image
    ${SDL2_TTF_LIBRARIES}
)