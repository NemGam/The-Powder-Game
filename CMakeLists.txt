cmake_minimum_required(VERSION 3.13)
project(ThePowderSim)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist)

add_executable(
    ${PROJECT_NAME}
)

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/src")

target_compile_options(${PROJECT_NAME} PRIVATE -O3)

target_link_libraries(
    ${PROJECT_NAME}
    glfw
)

install(DIRECTORY res TYPE DATA)
install(TARGETS ${PROJECT_NAME})

