cmake_minimum_required(VERSION 3.2)
project(aggup 
    VERSION 1.0.0 
    DESCRIPTION "Aggregator Updater" 
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(DEFAULT_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set (include_dest "include/aggup-${PROJECT_VERSION}")
set (lib_dest "lib/aggup-${PROJECT_VERSION}")

add_subdirectory(src)
add_subdirectory(tests)
