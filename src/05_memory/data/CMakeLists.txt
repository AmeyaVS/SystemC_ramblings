# check cmake version required
cmake_minimum_required(VERSION 3.5)

project(gen_ram C)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  ${PROJECT_NAME}
  gen_ram.c
  )

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  #OUTPUT ${PROJECT_SOURCE_DIR}/ram_init
  COMMAND ${PROJECT_NAME} 500
  COMMAND ${CMAKE_COMMAND} -E copy ram_init ${PROJECT_SOURCE_DIR}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

