project(world)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
file(GLOB_RECURSE ComponentObject_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ComponentObjects/*.*)
file(GLOB_RECURSE COMPONENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/components/*.*)

source_group("ComponentObjects" FILES ${ComponentObject_SRC_FILES})
source_group("components" FILES ${COMPONENT_SRC_FILES})

add_library(world ${SOURCE_FILES} ${ComponentObject_SRC_FILES} ${COMPONENT_SRC_FILES})
set_property(TARGET world PROPERTY FOLDER "ENGINE")

