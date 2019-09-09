project(test_client)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

link_directories(
	${WATER_THIRD_LIBRARY_DIRECTORY}/glfw3/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/boost/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/assimp
	${WATER_THIRD_LIBRARY_DIRECTORY}/irrXML
	${WATER_THIRD_LIBRARY_DIRECTORY}/zlib
	)

list(APPEND DEPEND_LIBS render world window filesystem common mesh)
list(APPEND THIRD_LIBS glfw3 assimp-${WATER_LIB_VERSION}-mtd zlibd irrXMLd)

add_executable(test_client ${SOURCE_FILES})
add_dependencies(test_client ${DEPEND_LIBS})
target_link_libraries(test_client ${DEPEND_LIBS} ${THIRD_LIBS})
set_property(TARGET test_client PROPERTY FOLDER "TEST")