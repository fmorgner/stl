cmake_minimum_required(VERSION 3.2)
project(sophia
  LANGUAGES CXX
  VERSION 0.0.1
  )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "The build type" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

set(CXX_VERSION "c++1z")
include("CompilerSetup")

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(HAS_PARENT)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sophia")
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

include_directories("include")


if(NOT SOPHIA_SKIP_EXAMPLES)
  add_subdirectory("src")
endif()

if(HAS_PARENT)
  set(SOPHIA_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)
endif()
