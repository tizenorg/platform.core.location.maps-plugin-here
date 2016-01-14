CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(pkg_name "maps-plugin-here")
PROJECT(${pkg_name} C CXX)

SET(CMAKE_INSTALL_PREFIX /usr)
SET(PREFIX ${CMAKE_INSTALL_PREFIX})

# Dependencies
SET(dependents 
	glib-2.0
	gmodule-2.0
	libxml-2.0
	dlog
	capi-maps-service
	capi-network-connection
	capi-appfw-app-manager
	capi-appfw-application
	evas
	ecore-evas
	elementary
	)

INCLUDE(FindPkgConfig)
pkg_check_modules(pkgs REQUIRED ${dependents})
FOREACH(flag ${pkgs_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
    SET(EXTRA_CXXFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)


# Build
SET(CMAKE_INSTALL_PREFIX /usr)
SET(PREFIX ${CMAKE_INSTALL_PREFIX})

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -fvisibility=hidden -fPIC -Wall -Werror")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS} -Wall -fPIC -std=c++0x -fvisibility=hidden")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DEXPORT_API=__attribute__((visibility(\"default\")))")
ADD_DEFINITIONS("-DTIZEN_DEBUG")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=${LIBDIR}")

# Main Include file
SET(INC_DIR
	inc
	inc/engine
)

INCLUDE_DIRECTORIES(
	${INC_DIR}
)

#This file must be corrected

# Source Lists
SET(SRCS
	# Maps API
	src/here_plugin.cpp

	# Here plug-in
	src/here_api.cpp
	src/here_base.cpp
	src/here_manager.cpp
	src/here_geocode.cpp
	src/here_place.cpp
	src/here_revgeocode.cpp
	src/here_multirevgeocode.cpp
	src/here_route.cpp
	src/here_utils.cpp
	src/here_view.cpp
	src/here_view_objects.cpp
)

ADD_LIBRARY(${pkg_name} SHARED ${SRCS})

SET_TARGET_PROPERTIES(${pkg_name}
	PROPERTIES
    VERSION ${FULLVER}
    SOVERSION ${MAJORVER}
    CLEAN_DIRECT_OUTPUT 1
)

FIND_LIBRARY(HERE_ENGINE heremaps-engine lib/${ARCH})

TARGET_LINK_LIBRARIES(${pkg_name} ${HERE_ENGINE} ${pkgs_LDFLAGS})

# Install
INSTALL(TARGETS ${pkg_name} DESTINATION ${LIBDIR}/maps/plugins)
INSTALL(FILES lib/${ARCH}/libheremaps-engine.so DESTINATION lib)

# Test Suite
#IF("${BINTYPE}" STREQUAL "eng")
#ENDIF("${BINTYPE}" STREQUAL "eng")

ADD_SUBDIRECTORY(heremaps-uc)
