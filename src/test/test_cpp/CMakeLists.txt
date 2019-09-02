project(test_cpp)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

add_executable(test_cpp ${SOURCE_FILES})
set_property(TARGET	test_cpp PROPERTY FOLDER "TEST")
add_dependencies(test_cpp common)