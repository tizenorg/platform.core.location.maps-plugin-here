CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("maps-plugin-here")

SET(PREFIX ${CMAKE_INSTALL_PREFIX})

INSTALL(FILES ${ARCH}/libmaps-plugin-here.so DESTINATION lib/maps/plugins)
INSTALL(FILES ${ARCH}/libheremaps-engine.so DESTINATION lib)
