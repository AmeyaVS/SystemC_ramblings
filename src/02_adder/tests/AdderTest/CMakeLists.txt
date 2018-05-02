# Check cmake version
cmake_minimum_required (VERSION 3.5)

project (AdderTest CXX)

# If building the tests from the library source directory.
if (NOT TARGET fullAdder::fullAdder)
  # Find fullAdder
  if (DEFINED ENV{FULLADDER_HOME})
    set (CMAKE_PREFIX_PATH "$ENV{FULLADDER_HOME}")
    find_package (fullAdder 0.1.0 CONFIG REQUIRED)
  else (DEFINED ENV{FULLADDER_HOME})
    message (FATAL_ERROR "Set the FULLADDER_HOME environment variable")
  endif (DEFINED ENV{FULLADDER_HOME})
endif(NOT TARGET fullAdder::fullAdder)

add_executable (
  ${PROJECT_NAME}.run
  src/driver.cpp
  src/monitor.cpp
  src/full_adder_main.cpp
  include/driver.h
  include/monitor.h
  )

include (CTest)

target_link_libraries (
  ${PROJECT_NAME}.run
  PRIVATE fullAdder::fullAdder
  )

target_include_directories (
  ${PROJECT_NAME}.run
  PRIVATE include
  )

set_property (
  TARGET ${PROJECT_NAME}.run
  PROPERTY CXX_STANDARD ${SystemC_CXX_STANDARD}
  )

add_test (
  NAME ${PROJECT_NAME}
  COMMAND ./${PROJECT_NAME}.run
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )
