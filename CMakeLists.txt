#
# CMake file to build FloatingPoint.
# Mark Grimes
# 19/Jan/2016
#

PROJECT( FloatingPoint )

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET( ${PROJECT_NAME}_MAJOR_VERSION 0 )
SET( ${PROJECT_NAME}_MINOR_VERSION 0 )
SET( ${PROJECT_NAME}_PATCH_LEVEL 0 )


ADD_DEFINITIONS( "-std=c++11" )

INCLUDE_DIRECTORIES( "${CMAKE_SOURCE_DIR}" )
AUX_SOURCE_DIRECTORY( "${CMAKE_SOURCE_DIR}" source_files )
MESSAGE( "source_files=${source_files}" )

# Add specific subset of the source files to the client code
SET( client_source_files "${CMAKE_SOURCE_DIR}/client.cpp" "${CMAKE_SOURCE_DIR}/FloatBits.cpp" )

SET( EMSCRIPTEN_ROOT_PATH "/usr/bin" )
SET( EMCXX "${EMSCRIPTEN_ROOT_PATH}/em++" )
SET( EMCC "${EMSCRIPTEN_ROOT_PATH}/emcc" )

SET( CLIENT_CODE_DIR "www" )
SET( client_destination_file "${CLIENT_CODE_DIR}/FloatingPoint.js" )
SET( html_destination_file "${CLIENT_CODE_DIR}/Example.html" )

add_custom_command( OUTPUT ${html_destination_file} ${CLIENT_CODE_DIR}
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CLIENT_CODE_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Example.html ${html_destination_file}
	DEPENDS Example.html )

add_custom_command( OUTPUT ${client_destination_file} ${CLIENT_CODE_DIR}
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CLIENT_CODE_DIR}
	COMMAND ${EMCXX} -O2 ${client_source_files} -o ${client_destination_file}
		-s EXPORT_NAME="'${PROJECT_NAME}'"
		-std=c++11
		--bind
		-I ${CMAKE_SOURCE_DIR}
	DEPENDS ${client_source_files} )

ADD_EXECUTABLE( ${PROJECT_NAME} ${source_files} ${client_destination_file} ${html_destination_file} )
