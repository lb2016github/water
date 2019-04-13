project(client)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

link_directories(${WATER_THIRD_LIBRARY_DIRECTORY}/glfw3 ${WATER_THIRD_LIBRARY_DIRECTORY}/boost)

list(APPEND DEPEND_LIBS render world window filesystem)
list(APPEND THIRD_LIBS glfw3)

add_executable(client ${SOURCE_FILES})
add_dependencies(client ${DEPEND_LIBS})
target_link_libraries(client ${DEPEND_LIBS} ${THIRD_LIBS})