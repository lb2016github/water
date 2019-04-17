project(common)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
# message(${SOURCE_FILES})

add_library(common ${SOURCE_FILES})

set_property(TARGET common PROPERTY FOLDER "ENGINE")