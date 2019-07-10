# Check cmake minimum versio required
cmake_minimum_required(VERSION 3.5)

project(SystemC_ramblings)

add_subdirectory(01_SystemCTest)
add_subdirectory(02_adder)
add_subdirectory(03_fir)
add_subdirectory(04_timer)
add_subdirectory(05_memory)
add_subdirectory(06_tlm_initial_example)
add_subdirectory(07_tlm_router)
add_subdirectory(08_tlm_router_example)
add_subdirectory(09_Doulos)

include(CTest)
