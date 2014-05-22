cmake_minimum_required(VERSION 2.8)
project(FactorItpp)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cotire/CMake/cotire)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Packages/bandit")
include_directories("${PROJECT_SOURCE_DIR}/Common")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP ")
else()
	# Assume GCC-style arguments
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wfatal-errors -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels")

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
			message(FATAL_ERROR "You need support for C++1y to build this package.")
			return()
		else()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
		endif()
	endif()

	if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
	endif()
endif()

#
# If we're on Mac OS we assume we have libc++, otherwise we assume
# we don't need it. (TODO: make this check more sofisticated)
#
if (CMAKE_HOST_APPLE AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

file(GLOB FactorItppSourceFiles FactorItpp/*.cpp FactorItpp/**/*.cpp)
add_library(factoritpp STATIC ${FactorItppSpecSourceFiles} )
cotire(factoritpp)

file(GLOB FactorItppSpecSourceFiles FactorItpp.Specs/*.cpp FactorItpp.Specs/**/*.cpp)
add_executable(factoritpp-specs ${FactorItppSpecSourceFiles} )
target_include_directories(factoritpp-specs "${PROJECT_SOURCE_DIR}/FactorItpp")
set_target_properties(factoritpp-specs PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "FactorItpp.Specs/Stubs.h")
set_target_properties(factoritpp-specs PROPERTIES COTIRE_ADD_UNIT_BUILD FALSE)
cotire(factoritpp-specs)

add_dependencies(factoritpp-specs factoritpp)

add_custom_command(TARGET factoritpp-specs
				   POST_BUILD
				   COMMAND factoritpp-specs --no-color --reporter=dots
				   WORKING_DIRECTORY ./bin)
