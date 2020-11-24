cmake_minimum_required(VERSION 3.13)
project(image_to_bytes LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Cairo)

add_executable(image-to-bytes main.cpp)

target_link_libraries(image-to-bytes PUBLIC ${CAIRO_LIBRARIES})
target_include_directories(image-to-bytes PUBLIC ${CAIRO_INCLUDE_DIRS})