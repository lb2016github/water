project(mesh)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
include_directories(${WATER_THIRD_INCLUDE_DIRECTORY}/assimp)

add_library(mesh ${SOURCE_FILES})
set_property(TARGET mesh PROPERTY FOLDER "ENGINE")

