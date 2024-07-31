cmake_minimum_required(VERSION 3.13)

add_executable(
    ${PROJECT_NAME}
    application.cpp
    input_manager.cpp
    random.cpp
    utils.cpp
)

install()