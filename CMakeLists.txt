cmake_minimum_required(VERSION 3.10)

project(snake-game)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)

FetchContent_MakeAvailable(SFML)

set(SOURCES
    ./src/game.cpp
    ./src/grid.cpp
    ./src/gridCell.cpp
    ./src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)

if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Copy SFML DLLs after build (only on Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-main>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
