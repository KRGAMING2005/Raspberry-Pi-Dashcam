cmake_minimum_required(VERSION 3.25.1)

project(Dashcam
    VERSION 1.0.0)

file(GLOB_RECURSE HEADER_DIR "src/*.hpp")
file(GLOB_RECURSE SOURCE_DIR "src/*.cpp")

find_package(OpenCV REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

if(DEFINED NO_PI_CAMERA)
    add_compile_definitions(NO_CAMERA)
endif()

include_directories(${Qt6_INCLUDE})
add_executable(${PROJECT_NAME} ${HEADER_DIR} ${SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})