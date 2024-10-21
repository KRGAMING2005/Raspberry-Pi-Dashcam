cmake_minimum_required(VERSION 3.25.1)

project(Dashcam
    VERSION 1.0.0)

FILE(GLOB SOURCE_DIR "src/*.cpp")

find_package(OpenCV REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)

include_directories(${LIBCAMERA_INCLUDE_DIRS})

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${LIBCAMERA_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${LIBCAMERA_CFLAGS_OTHER})