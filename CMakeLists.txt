cmake_minimum_required(VERSION 3.10.2)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(VMMail)

IF(NOT CMAKE_BUILD_TYPE)
	SET(
		CMAKE_BUILD_TYPE
		"Debug"
		CACHE STRING
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

IF(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	ADD_DEFINITIONS(-DDEBUG)
ENDIF(${CMAKE_BUILD_TYPE} STREQUAL Debug)

find_package(wxWidgets REQUIRED core base webview)
include(${wxWidgets_USE_FILE})

find_package(Vmime REQUIRED)
include_directories(${VMIME_INCLUDE_DIR})

if(WIN32)
	file(GLOB project_SRCS src/formbuilder/*.h src/formbuilder/*.cpp src/*.h src/*.cpp src/VMMail.rc src/mingw-std-threads/*.h)
	add_executable(VMMail WIN32 ${project_SRCS})
else(WIN32)
	file(GLOB project_SRCS src/formbuilder/*.h src/formbuilder/*.cpp src/*.h src/*.cpp src/VMMail.rc)
    add_executable(VMMail ${project_SRCS})
endif(WIN32)

target_link_libraries(VMMail ${wxWidgets_LIBRARIES}	${VMIME_LIBRARIES})

target_include_directories(VMMail PRIVATE ${wxWidgets_INCLUDE_DIRS})

file(COPY "${CMAKE_SOURCE_DIR}/src/bitmaps/throbber.gif" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")