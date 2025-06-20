cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main 
    src/App.cpp
    src/MenuScreen.cpp
    src/GameScreen.cpp
    src/ScoresScreen.cpp

    src/main.cpp
)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(ASSETS_SRC_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DST_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SRC_DIR} ${ASSETS_DST_DIR}
)


target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
