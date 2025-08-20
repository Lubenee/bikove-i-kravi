cmake_minimum_required(VERSION 3.10.0)
project(bikove-i-kravi VERSION 0.1.0 LANGUAGES C CXX)

# Specify the directories for source files and header files
include_directories(Headers) # Add Headers folder for header files

file(GLOB SOURCES "src/*.cpp")
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


target_include_directories(${PROJECT_NAME} PRIVATE Headers)