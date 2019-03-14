project(client)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

list(APPEND DEPEND_LIBS render world window)

add_executable(client ${SOURCE_FILES})
add_definitions(client ${DEPEND_LIBS})
target_link_libraries(client ${DEPEND_LIBS})