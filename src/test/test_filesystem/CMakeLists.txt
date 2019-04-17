project(test_filesystem)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

link_directories(${WATER_THIRD_LIBRARY_DIRECTORY}/glfw3 ${WATER_THIRD_LIBRARY_DIRECTORY}/boost)

add_executable(test_filesystem ${SOURCE_FILES})
target_link_libraries(test_filesystem filesystem common)
set_property(TARGET	test_filesystem PROPERTY FOLDER "TEST")
add_dependencies(test_filesystem common)