set(target hybrid)
project(${target} C CXX)
cmake_minimum_required(VERSION 2.8.12)

message(STATUS "operation system is ${CMAKE_SYSTEM}") 

message("PROJECT_SOURCE_DIR:"		${PROJECT_SOURCE_DIR})
message("CMAKE_BINARY_DIR:"			${CMAKE_BINARY_DIR})
message("PROJECT_BINARY_DIR :"		${PROJECT_BINARY_DIR})
message("CMAKE_SOURCE_DIR :"		${CMAKE_SOURCE_DIR})
message("CMAKE_CURRENT_LIST_FILE:"	${CMAKE_CURRENT_LIST_FILE})

add_subdirectory(sdk)

aux_source_directory(. SRCS)      
pybind11_add_module(${target} ${SRCS})

if(MSVC)
	target_compile_options(${target} PRIVATE /utf-8)
endif()

message("cmake build end")
