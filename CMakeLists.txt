#
# Copyright Barco N.V. All Rights Reserved.
#
message(STATUS "\n-- || Processing cml - starting")

cmake_minimum_required( VERSION 3.14 )
project( cml VERSION 1.0.3 )

########################################################################
# cml header only library
########################################################################
add_library(cml INTERFACE)
add_library(cml::cml ALIAS cml )

target_include_directories(cml  SYSTEM INTERFACE # TODO_MADAU: is SYSTEM needed
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>  
)

########################################################################
# Installation
########################################################################
include(GNUInstallDirs) # provides CMAKE_INSTALL_{INCLUDE|LIB|BIN}DIR variables
include(CMakePackageConfigHelpers) # provides write_basic_package_version_file()


#### Copy header files ####
install(DIRECTORY cml
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

### cmake files ###
# Create cmlConfigVersion.cmake
set( version_config "${CMAKE_CURRENT_BINARY_DIR}/cmlConfigVersion.cmake" )
write_basic_package_version_file( "${version_config}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion )

# Create cmlTargets.cmake
install( TARGETS cml
    EXPORT cmlConfigTargets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cml )
export( TARGETS cml NAMESPACE cml:: FILE cmlTargets.cmake )

# Install files
if( WIN32 AND NOT CYGWIN)
    set( CONFIG_LOC CMake )
else( )
    set( CONFIG_LOC "${CMAKE_INSTALL_LIBDIR}/cmake/cml" )
endif( )
install( EXPORT cmlConfigTargets
  FILE cmlTargets.cmake
  NAMESPACE cml::
  DESTINATION ${CONFIG_LOC} )

install (
  FILES CMake/cmlConfig.cmake "${version_config}"
  DESTINATION ${CONFIG_LOC})

message(STATUS "|| Processing project cml - finished\n")
