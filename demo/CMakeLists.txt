cmake_minimum_required(VERSION 3.10)
project(Demo LANGUAGES CXX)

add_subdirectory(.. tiny-ui-build)

add_executable(Demo
    main.cpp
)

target_link_libraries(Demo
    PRIVATE tiny-ui
)

add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Demo>/assets)