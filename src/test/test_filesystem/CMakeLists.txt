project(common)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
# message(${SOURCE_FILES})

# add_library(math3d ${SOURCE_FILES})
#set_target_properties(math3d
#PROPERTIES
#LINKER_LANGUAGE C++
#)

add_custom_target(common
	SOURCES ${SOURCE_FILES}
)
set_property(TARGET common PROPERTY FOLDER "ENGINE")