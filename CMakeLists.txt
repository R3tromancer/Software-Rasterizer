cmake_minimum_required(VERSION 3.20)

project(SoftwareRasterizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3)

add_executable(rasterizer
    src/main.cpp
    src/Framebuffer.cpp
    src/Rasterizer.cpp
    src/Display.cpp
    src/math/Geometry2D.cpp
)

target_link_libraries(rasterizer PRIVATE SDL3::SDL3)

add_custom_command(TARGET rasterizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t
        $<TARGET_FILE_DIR:rasterizer>
        $<TARGET_RUNTIME_DLLS:rasterizer>
    COMMAND_EXPAND_LISTS
)