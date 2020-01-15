project(client)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

link_directories(
	${WATER_THIRD_LIBRARY_DIRECTORY}/glfw3/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/boost/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/assimp/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/irrXML/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/zlib/${WATER_LIB_VERSION}
	${WATER_THIRD_LIBRARY_DIRECTORY}/freetype
	)

list(APPEND DEPEND_LIBS render world window filesystem common math3d)
list(APPEND THIRD_LIBS glfw3 assimp-${WATER_LIB_VERSION}-mtd zlibd irrXMLd freetype)

add_executable(client ${SOURCE_FILES})
add_dependencies(client ${DEPEND_LIBS})
target_link_libraries(client ${DEPEND_LIBS} ${THIRD_LIBS})
set_property(TARGET client PROPERTY FOLDER "ENGINE")

SET(DST_DIR ${CMAKE_BINARY_DIR}/client/Debug)
add_custom_command(
	TARGET client
	POST_BUILD
	COMMAND echo "text"
	COMMAND ${CMAKE_COMMAND} -E copy ${WATER_THIRD_LIBRARY_DIRECTORY}/assimp/${WATER_LIB_VERSION}/assimp-${WATER_LIB_VERSION}-mtd.dll ${DST_DIR}/assimp-${WATER_LIB_VERSION}-mtd.dll
	COMMAND ${CMAKE_COMMAND} -E copy ${WATER_THIRD_LIBRARY_DIRECTORY}/zlib/${WATER_LIB_VERSION}/zlibd.dll ${DST_DIR}/zlibd.dll
	COMMAND ${CMAKE_COMMAND} -E copy ${WATER_THIRD_LIBRARY_DIRECTORY}/freetype/freetype.dll ${DST_DIR}/freetype.dll
	COMMENT ${CMAKE_BINARY_DIR}/assimp-${WATER_LIB_VERSION}-mtd.dll
)