cmake_minimum_required(VERSION 3.20)

# Project metadata and enabled languages.
# C is needed because GLAD is compiled from a C source file (glad.c).
project(ting VERSION 0.1.0 LANGUAGES CXX C)

# Global C++ language level for project targets.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build GLFW from local source, but skip optional targets
# (docs/tests/examples/install) to keep this project lean.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(Dependancies/GLFW)

# GLAD: OpenGL function loader library.
add_library(glad STATIC
    Dependancies/GLAD/glad.c
)
target_include_directories(glad
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependancies/GLAD
)

# Dear ImGui core + GLFW/OpenGL3 backend implementation files.
add_library(imgui STATIC
    Dependancies/ImGui/imgui.cpp
    Dependancies/ImGui/imgui_draw.cpp
    Dependancies/ImGui/imgui_tables.cpp
    Dependancies/ImGui/imgui_widgets.cpp
    Dependancies/ImGui/backends/imgui_impl_glfw.cpp
    Dependancies/ImGui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependancies/ImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependancies/ImGui/backends
)
# imgui_impl_glfw.cpp uses GLFW API symbols.
target_link_libraries(imgui PUBLIC glfw)

# Main application target.
add_executable(ting
    Source/Main.cpp
    Source/Application.cpp
    Source/Logger/Logger.cpp
)

# Allow headers in Source to be included as "HeaderName.hpp".
target_include_directories(ting
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependancies/GLFW/include
)

# Link order/components for the app:
# - glad: runtime OpenGL function loading
# - imgui: UI library + backend bridge code
# - glfw: window/context/input
# - opengl32: Windows OpenGL system library
target_link_libraries(ting
    PRIVATE
        glad
        imgui
        glfw
        opengl32
)