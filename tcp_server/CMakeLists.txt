cmake_minimum_required(VERSION 3.16)

project(tcp_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES "src/*.c*")
file(GLOB HDR_FILES "include/*.h*")

include_directories(include)
include_directories(${TCP_LIB_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} tcp)