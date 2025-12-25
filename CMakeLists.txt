cmake_minimum_required(VERSION 3.10.0)
project(tiny-ui VERSION 1.3.5 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

add_library(tiny-ui
    src/tiny_handler.cpp
    src/tiny_interface.cpp
    src/tiny_module.cpp
    src/tiny_text.cpp
    src/tiny_ui.cpp
    src/tiny_vector.cpp
)

target_include_directories(tiny-ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(tiny-ui
    PUBLIC
        ${SDL2_LIBRARIES}
        SDL2_image
        ${SDL2_TTF_LIBRARIES}
)