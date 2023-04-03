# check cmake version required
cmake_minimum_required(VERSION 3.5)

project(06_tlm_initial_example CXX)

include(CTest)

set(CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})

find_package(SystemCLanguage CONFIG REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

source_group("Sources" FILES
  testbench.cpp
  design.cpp
  initiator.cpp
  target.cpp
)

source_group("Headers" FILES
  top.h
  report.h
  initiator.h
  target.h
)

add_executable(
  ${PROJECT_NAME}.run
  testbench.cpp
  design.cpp
  initiator.cpp
  target.cpp
  top.h
  report.h
  initiator.h
  target.h
  )

target_include_directories(${PROJECT_NAME}.run
  PRIVATE ${PROJECT_SOURCE_DIR}
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
