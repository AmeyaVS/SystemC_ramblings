# Check the cmake version required
cmake_minimum_required (VERSION 3.5)

# Set the project name and the version number.
project (
  fullAdder      # Project Name
  VERSION 0.1.0  # Project Version: Major.Minor.Patch
  LANGUAGES CXX  # Project Type
  )

# Print Project Information
message (STATUS "Project Name: ${PROJECT_NAME}, Version: ${PROJECT_VERSION}")

# Check for SystemC dependency
set (CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})

# Find SystemC package
find_package (SystemCLanguage CONFIG REQUIRED)

# Export CXX Compilation Commands.
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Documentation Option
option (BUILD_DOC "Build Documentation" OFF)
message (STATUS "Build Documentation: ${BUILD_DOC}")

# Set Build Shared Library
option (BUILD_SHARED_LIBS "Build Shared Library" OFF)
message (STATUS "Build Shared Library: ${BUILD_SHARED_LIBS}")

# Add the library target
add_library (
  ${PROJECT_NAME} # Add the library target.
  SHARED
  src/full_adder.cpp
  src/half_adder.cpp
  )

# Add the sources for the targets.
# Include all the header files in the project to be made visible in the IDE's.
target_sources (
  ${PROJECT_NAME}
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/full_adder.h>
  $<INSTALL_INTERFACE:include/full_adder.h>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/half_adder.h>
  $<INSTALL_INTERFACE:include/half_adder.h>
  )

# Adding source group's for logically segregating the source files in a group.
# This option is only for current project.
source_group (
  "HeaderFiles"
  FILES include/full_adder.h
        include/half_adder.h  # relative path for the header file.
  )

source_group (
  "SourceFiles"
  FILES src/full_adder.cpp
        src/half_adder.cpp  # relative path for the header file.
  )

# Target include directory
target_include_directories (
  ${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )

# Target Link libraries
target_link_libraries (
  ${PROJECT_NAME}
  PUBLIC SystemC::systemc
  )

# Set target property
set_property (
  TARGET ${PROJECT_NAME}
  PROPERTY CXX_STANDARD ${SystemC_CXX_STANDARD}
  )

# Using the standard UNIX style layout for the project.
include (GNUInstallDirs)

# Exporting the targets.
install (
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  PUBLIC_HEADER DESTINATION include
  COMPONENT dev
  )

# Install the header file.
install (
  FILES ${PROJECT_SOURCE_DIR}/include/full_adder.h
        ${PROJECT_SOURCE_DIR}/include/half_adder.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT dev
  )

# Export the targets.
install (
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
  )

# Create a pseudo target for the exported target.
# Required when building the tests from the projects directory.
add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Include the CMake Package Auto generators.
include (CMakePackageConfigHelpers)

# Configure the Package Config file.
configure_package_config_file (
  cmake/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  )

# Create a basic Package Version file.
write_basic_package_version_file (
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  )

# Install the generated config files.
install (
  FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION lib/cmake/${PROJECT_NAME}
  COMPONENT dev
  )

# Enable Testing
include (CTest)

# Include Unit Test directory.
add_subdirectory (tests)
# add_subdirectory (examples)

# Installing existing tests as examples for the project.
install (
  DIRECTORY ${PROJECT_SOURCE_DIR}/tests/
  DESTINATION ${CMAKE_INSTALL_DOCDIR}/examples
  COMPONENT doc
  )

# Build Documentation
if (BUILD_DOC)
  find_package (Doxygen)

  if (DOXYGEN_FOUND)
    # Configure Doxyfile
    configure_file (
      ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in
      Doxyfile
      @ONLY
      )

    # Adding documentation as target.
    add_custom_target (
      docs
      ALL
      COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      COMMENT "Generating API Documentation"
      VERBATIM
      )

    # Adding install target for docs.
    install (
      DIRECTORY ${PROJECT_BINARY_DIR}/docs
      DESTINATION ${CMAKE_INSTALL_DOCDIR}
      COMPONENT doc
      )
  else (DOXYGEN_FOUND)
    message (FATAL_ERROR "Doxygen is needed to generate the documentation.")
  endif (DOXYGEN_FOUND)
endif(BUILD_DOC)

option (BUILD_PACKAGE "CPack based packaging" OFF)
message (STATUS "Build Package : ${BUILD_PACKAGE}")

if (BUILD_PACKAGE)
  # Setting up veriables for packaging.
  if (WIN32 AND NOT UNIX)
    set (CPACK_GENERATOR "ZIP")
  else (WIN32 AND NOT UNIX)
    set (CPACK_GENERATOR "DEB;ZIP")
  endif (WIN32 AND NOT UNIX)

  # Set the packaging version.
  set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
  SET (CPACK_PACKAGE_DESCRIPTION_SUMMARY "FullAdder Library Package")
  # Packaing the library
  include (CPackConfig.cmake)

  include (CPack)
endif (BUILD_PACKAGE)
