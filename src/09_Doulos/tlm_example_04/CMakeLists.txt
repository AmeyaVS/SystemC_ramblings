# check cmake version required
cmake_minimum_required(VERSION 3.5)

project(tlm_example_04 CXX)

include(CTest)

set(CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})

find_package(SystemCLanguage CONFIG REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

source_group("Sources" FILES
  testbench.cpp
  )

source_group("Headers" FILES
  initiator.h
  target.h
  top.h
  utilities.h
  )

add_executable(
  ${PROJECT_NAME}.run
  testbench.cpp
  initiator.h
  target.h
  top.h
  utilities.h
  )

target_compile_definitions(${PROJECT_NAME}.run
  PRIVATE _CRT_SECURE_NO_WARNINGS
  )

target_link_libraries(
  ${PROJECT_NAME}.run
  PRIVATE SystemC::systemc
  )

set_property(
  TARGET ${PROJECT_NAME}.run
  PROPERTY CXX_STANDARD ${SystemC_CXX_STANDARD}
  )

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ./${PROJECT_NAME}.run
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )
