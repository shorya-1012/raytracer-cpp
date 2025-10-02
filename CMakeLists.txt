cmake_minimum_required(VERSION 4.1)


project(raytracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} 
  ${SOURCE_DIR}/main.cpp
)


