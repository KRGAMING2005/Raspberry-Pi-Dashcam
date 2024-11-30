cmake_minimum_required(VERSION 3.25.1)

project(Dashcam
    VERSION 1.0.0)

file(GLOB_RECURSE HEADER_DIR "src/*.hpp")
file(GLOB_RECURSE SOURCE_DIR "src/*.cpp")

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} ${HEADER_DIR} ${SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})