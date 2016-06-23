CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(heremaps-uc-launcher C)
SET(PKG_NAME heremaps-uc-launcher)

# Version control
SET(VERSION_MAJOR 0)
SET(VERSION "${VERSION_MAJOR}.0.1")

# Architecture
FIND_PROGRAM(UNAME NAMES uname)
EXEC_PROGRAM("${UNAME}" ARGS "-m" OUTPUT_VARIABLE "ARCH")
IF("${ARCH}" STREQUAL "arm")
    ADD_DEFINITIONS("-D_SOUND_EQ_ARCH_ARM_")
ENDIF()

SET(COMMON_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")

SET(UC_LAUNCHER_PREFIX /usr)
SET(BINDIR "${UC_LAUNCHER_PREFIX}/bin")

IF("${CMAKE_BUILD_TYPE}" STREQUAL "")
	SET(CMAKE_BUILD_TYPE "Release")
ENDIF("${CMAKE_BUILD_TYPE}" STREQUAL "")
MESSAGE("Build type: ${CMAKE_BUILD_TYPE}")

INCLUDE(FindPkgConfig)

CONFIGURE_FILE(org.tizen.lbs.Providers.HereMapsUCLauncher.service.in org.tizen.lbs.Providers.HereMapsUCLauncher.service @ONLY)
INSTALL(FILES org.tizen.lbs.Providers.HereMapsUCLauncher.service DESTINATION /usr/share/dbus-1/services)
INSTALL(FILES config/heremaps-uc-launcher.conf DESTINATION ${SYSCONF_DIR}/dbus-1/session.d)

# Check external libraries
INCLUDE(FindPkgConfig)
pkg_check_modules(UC_LAUNCHER_EXT_LIBS REQUIRED glib-2.0 gio-2.0 gio-unix-2.0 gthread-2.0 capi-appfw-application capi-system-info evas dlog ecore)

SET(EXTRA_CFLAGS "")
FOREACH(flag ${${UC_LAUNCHER_EXT_LIBS}_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${COMMON_C_FLAGS} ${EXTRA_CFLAGS}")

ADD_DEFINITIONS("-DUC_LAUNCHER_PKG=\"${PKG_NAME}\"")

ADD_SUBDIRECTORY(src)
