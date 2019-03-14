project(window)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

link_directories(${CMAKE_SOURCE_FILE}/../libs/glfw3)

add_library(window ${SOURCE_FILES})