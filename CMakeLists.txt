cmake_minimum_required(VERSION 3.10)

project(azoya)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(GAME_SRC ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
             ${CMAKE_CURRENT_LIST_DIR}/src/game.cpp
             ${CMAKE_CURRENT_LIST_DIR}/src/dialog_box.cpp)

add_executable(game ${GAME_SRC})
target_include_directories(game PUBLIC include/)
target_compile_features(game PRIVATE cxx_std_23)
target_link_libraries(game PRIVATE SFML::Graphics)

install(TARGETS game RUNTIME DESTINATION bin)
