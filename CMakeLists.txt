cmake_minimum_required(VERSION 3.24)

project(
    Game
    VERSION 0.1.0
    DESCRIPTION "A rogue-like game coded in C++ with raylib"
    LANGUAGES C CXX
)

option(GAME_ENABLE_CLANG_TIDY "Run clang-tidy while compiling Game" OFF)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Keep the dependency reproducible by tracking a released raylib tag, not its
# development branch.
set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(Game
    src/main.cpp
        src/kernel/window.cpp
        src/kernel/engine.cpp
        src/kernel/logger.cpp
)

target_compile_features(Game PRIVATE cxx_std_23)
set_target_properties(
    Game
    PROPERTIES
        CXX_EXTENSIONS OFF
)

target_include_directories(Game PRIVATE include)
target_link_libraries(Game PRIVATE raylib)

# add_custom_command(
#     TARGET Game
#     POST_BUILD
#     COMMAND
#         ${CMAKE_COMMAND} -E copy_directory
#         "${CMAKE_CURRENT_SOURCE_DIR}/src/assets"
#         "$<TARGET_FILE_DIR:Game>/assets"
#     COMMENT "Copying Game assets"
# )

if(GAME_ENABLE_CLANG_TIDY)
    find_program(
        GAME_CLANG_TIDY_EXECUTABLE
        NAMES clang-tidy clang-tidy-22 clang-tidy-21 clang-tidy-20 clang-tidy-19 clang-tidy-18
        REQUIRED
    )
    set_target_properties(
        Game
        PROPERTIES
            CXX_CLANG_TIDY
                "${GAME_CLANG_TIDY_EXECUTABLE};--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy"
    )
endif()

if(MSVC)
    target_compile_options(Game PRIVATE /W4 /permissive-)
else()
    target_compile_options(Game PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()
