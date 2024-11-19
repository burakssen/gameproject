cmake_minimum_required(VERSION 3.29)

project(gameproject)

set(CMAKE_CXX_STANDARD 23)

set(BUILD_SHARED_LIBS ON)
add_subdirectory(vendor/raylib EXCLUDE_FROM_ALL)

file(GLOB_RECURSE GAME_SOURCES "src/game/*.cpp")
file(GLOB_RECURSE INTERFACE_SOURCES "src/interface/*.cpp" "src/main.cpp")

set(DYNAMICLIB_EXPORT 1)
add_library(game SHARED ${GAME_SOURCES})
add_executable(gameproject ${INTERFACE_SOURCES})

# Ensure proper shared library handling
set_target_properties(game PROPERTIES 
    VISIBILITY_INLINES_HIDDEN ON
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(game PRIVATE src ${RAYLIB_INCLUDE_DIRS} vendor/entt/single_include)
target_link_libraries(game PRIVATE raylib)

target_include_directories(gameproject PRIVATE src ${RAYLIB_INCLUDE_DIRS} vendor/entt/single_include)
target_link_libraries(gameproject PRIVATE raylib)
