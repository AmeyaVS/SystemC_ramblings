# check cmake version required
cmake_minimum_required(VERSION 3.5)

project(02_adder CXX)

include(CTest)

set(CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})

find_package(SystemCLanguage CONFIG REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  ${PROJECT_NAME}.run
  driver.cpp
  full_adder.cpp
  full_adder_main.cpp
  half_adder.cpp
  monitor.cpp
  )

target_include_directories(
  ${PROJECT_NAME}.run
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
