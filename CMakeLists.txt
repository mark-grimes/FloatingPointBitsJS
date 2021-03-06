#
# CMake file to build FloatingPoint.
# Mark Grimes
# 19/Jan/2016
# MIT licence, see http://opensource.org/licenses/MIT
#

PROJECT( FloatingPoint )

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET( ${PROJECT_NAME}_MAJOR_VERSION 0 )
SET( ${PROJECT_NAME}_MINOR_VERSION 0 )
SET( ${PROJECT_NAME}_PATCH_LEVEL 0 )


ADD_DEFINITIONS( "-std=c++11" )

INCLUDE_DIRECTORIES( "${CMAKE_SOURCE_DIR}" )

# Add specific subset of the source files to the client code
SET( client_source_files "${CMAKE_SOURCE_DIR}/client.cpp" "${CMAKE_SOURCE_DIR}/FloatBits.cpp" )

IF( EMSCRIPTEN_ROOT_PATH )
	MESSAGE( "-- EMSCRIPTEN_ROOT_PATH set to \"${EMSCRIPTEN_ROOT_PATH}\"" )
ELSE()
	SET( EMSCRIPTEN_ROOT_PATH "/usr/bin" )
	MESSAGE( "-- EMSCRIPTEN_ROOT_PATH was not set, so trying \"${EMSCRIPTEN_ROOT_PATH}\"." )
	MESSAGE( "--      If this is incorrect, invoke cmake with \"-DEMSCRIPTEN_ROOT_PATH=<path to em++>\"" )
ENDIF()
SET( EMCXX "${EMSCRIPTEN_ROOT_PATH}/em++" )
SET( EMCC "${EMSCRIPTEN_ROOT_PATH}/emcc" )

SET( CLIENT_CODE_DIR "${CMAKE_BINARY_DIR}/www" )
SET( client_destination_file "${CLIENT_CODE_DIR}/FloatingPoint.js" )
SET( CLIENT_STATIC_FILES "Example.html" "Tests.html" )

add_custom_command( OUTPUT ${CLIENT_CODE_DIR}
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CLIENT_CODE_DIR} )

foreach( FILE ${CLIENT_STATIC_FILES} )
	SET( INPUT_FILE "${CMAKE_SOURCE_DIR}/${FILE}" )
	SET( OUTPUT_FILE "${CLIENT_CODE_DIR}/${FILE}" )

	add_custom_command( OUTPUT ${OUTPUT_FILE}
		COMMAND ${CMAKE_COMMAND} -E copy "${INPUT_FILE}" "${OUTPUT_FILE}"
		DEPENDS ${INPUT_FILE} ${CLIENT_CODE_DIR} )
	list( APPEND CLIENT_STATIC_OUTPUT "${OUTPUT_FILE}" )
endforeach( FILE )

add_custom_command( OUTPUT ${client_destination_file}
	COMMAND ${EMCXX} -O3 ${client_source_files} -o ${client_destination_file}
		-s EXPORT_NAME="'${PROJECT_NAME}'"
		-s MODULARIZE=1
		-std=c++11
		--bind
		-I ${CMAKE_SOURCE_DIR}
	DEPENDS ${client_source_files} ${CLIENT_CODE_DIR} )

add_custom_target( "${PROJECT_NAME}ClientCode" ALL DEPENDS ${CLIENT_STATIC_OUTPUT} ${client_destination_file} )
