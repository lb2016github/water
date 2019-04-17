project(filesystem)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
include_directories({WATER_THIRD_INCLUDE_DIRECTORY}/pugixml)

add_library(filesystem ${SOURCE_FILES})
set_property(TARGET filesystem PROPERTY FOLDER "ENGINE")
add_dependencies(filesystem common)

