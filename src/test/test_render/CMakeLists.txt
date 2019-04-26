project(test_render)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

link_directories(${WATER_THIRD_LIBRARY_DIRECTORY}/glfw3 ${WATER_THIRD_LIBRARY_DIRECTORY}/boost/${WATER_LIB_VERSION})

add_executable(test_render ${SOURCE_FILES})
target_link_libraries(test_render filesystem common render)
set_property(TARGET	test_render PROPERTY FOLDER "TEST")
add_dependencies(test_render common render)