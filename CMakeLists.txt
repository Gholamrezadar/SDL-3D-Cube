cmake_minimum_required(VERSION 3.22)

project(SDL_TEST_PRJ)
# find_package(glm REQUIRED)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# include files
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${GLM_INCLUDE_DIRS})

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable
add_executable(sdl_app ${SOURCES})

# Link against the SDL library
target_link_libraries(sdl_app SDL2)
# target_link_libraries(sdl_app glm)

# Set C++ standard to C++11
set_property(TARGET sdl_app PROPERTY CXX_STANDARD 11)

