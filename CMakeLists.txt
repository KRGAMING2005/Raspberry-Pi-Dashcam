cmake_minimum_required(VERSION 3.25.1)

project(Dashcam
    VERSION 1.0.0)

FILE(GLOB SOURCE_DIR "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_DIR})