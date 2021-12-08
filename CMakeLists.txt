cmake_minimum_required(VERSION 2.8)

project(project-cells)
add_executable(project-cells ./src/main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(project-cells ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
