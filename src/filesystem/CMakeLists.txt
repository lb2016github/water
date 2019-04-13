project(filesystem)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

add_library(filesystem ${SOURCE_FILES})
set_property(TARGET filesystem PROPERTY FOLDER "ENGINE")

