cmake_minimum_required(VERSION 3.1)

find_package(Doxygen)

option(BUILD_DOCUMENTATION "Create and install documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(DOXYGEN_FOUND)

	set(DOXYGEN ${CMAKE_SOURCE_DIR}/doxygen/Doxyfile.in)

	add_custom_target(
		docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN}
		VERBATIM
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doxygen
	)

endif()

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED on)

set(PROJECT_NAME Tetris)

project(${PROJECT_NAME})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

set(SOURCE_FILES 
	game.h 
	game.cpp
	save_load.h
	save_load.cpp
        main.cpp )

set(SFML_ROOT ${CMAKE_SOURCE_DIR}/SFML-2.4.2)

set(SFML_STATIC_LIBRARIES FALSE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.4.2/cmake/Modules")

find_package(SFML REQUIRED COMPONENTS audio graphics window system)

include_directories(${SFML_INCLUDE_DIR})

add_executable (${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

install(FILES 
	${CMAKE_SOURCE_DIR}/SFML-2.4.2/bin/sfml-graphics-2.dll
	${CMAKE_SOURCE_DIR}/SFML-2.4.2/bin/sfml-system-2.dll
	${CMAKE_SOURCE_DIR}/SFML-2.4.2/bin/sfml-window-2.dll 
	DESTINATION ${CMAKE_SOURCE_DIR}/game
	CONFIGURATIONS Release)

install(FILES 
	${CMAKE_SOURCE_DIR}/SFML-2.4.2/bin/sfml-graphics-d-2.dll
	${CMAKE_SOURCE_DIR}/SFML-2.4.2/bin/sfml-system-d-2.dll
	${CMAKE_SOURCE_DIR}/SFML-2.4.2/bin/sfml-window-d-2.dll 
	DESTINATION ${CMAKE_SOURCE_DIR}/game
	CONFIGURATIONS Debug)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/images 
	DESTINATION ${CMAKE_SOURCE_DIR}/game)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data 
	DESTINATION ${CMAKE_SOURCE_DIR}/game)

install(TARGETS ${PROJECT_NAME} 
	DESTINATION ${CMAKE_SOURCE_DIR}/game)
