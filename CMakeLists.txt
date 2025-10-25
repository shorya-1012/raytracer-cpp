cmake_minimum_required(VERSION 4.1)

project(raytracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} 
  ${SOURCE_DIR}/main.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)


