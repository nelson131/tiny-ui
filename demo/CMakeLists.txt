cmake_minimum_required(VERSION 3.10)
project(Demo LANGUAGES CXX)

add_subdirectory(.. tiny-ui-build)

add_executable(Demo
    main.cpp
)

target_link_libraries(Demo
    PRIVATE tiny-ui
)
