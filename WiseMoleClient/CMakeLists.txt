cmake_minimum_required(VERSION 3.10)

# Set the project name and specify C++ as the language
project(WiseMoleClient LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

# Add compiler warnings for g++ to find issues early
add_compile_options(-Wall -Wextra -Wpedantic)

# Define the final executable name and its source files
add_executable(WiseMoleClient
    main.cpp
    SDLGame.cpp
    SoundMgr.cpp
    VideoModeMgr.cpp
    game_objects/Box.cpp
    game_objects/BoxPlace.cpp
    game_objects/CollisionCaps.cpp
    game_objects/GameObject.cpp
    game_objects/MainHero.cpp
    game_objects/WallBlock.cpp
)

target_link_libraries(WiseMoleClient PRIVATE SDL3::SDL3)
target_link_libraries(WiseMoleClient PRIVATE SDL3_image::SDL3_image-shared)
target_link_libraries(WiseMoleClient PRIVATE SDL3_mixer::SDL3_mixer-shared)
target_link_libraries(WiseMoleClient PRIVATE SDL3_ttf::SDL3_ttf-shared)

install(CODE "
  message(STATUS \"Copy assets\")
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ../assets/ assets)
")
