cmake_minimum_required(VERSION 2.8.9)
project(Vesyla)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
# set(CMAKE_AUTOMOC ON)
# Show verbose command while compiling
#set(CMAKE_VERBOSE_MAKEFILE ON)

# The project version number.
set(VERSION_MAJOR 2 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost COMPONENTS regex system filesystem program_options unit_test_framework graph REQUIRED)
find_package(Gecode)

include_directories(/usr/local/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(src)

file(GLOB SOURCES_UTIL "src/util/*.cpp" "src/util/*/*.cpp" "src/util/*/*.cc")
file(GLOB SOURCES_VIR "src/VIR/*.cpp")
file(GLOB SOURCES_BIR "src/BIR/*.cpp")
file(GLOB SOURCES_SCHEDULE "src/schedule/*.cpp")
file(GLOB SOURCES_EXEC "src/exec/*.cpp")

set(CMAKE_CXX_FLAGS "-std=c++11 -w -pedantic -lpthread -g -O1 -DBOOST_LOG_DYN_LINK")
set(PROJECT_LINK_LIBS)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(Util SHARED ${SOURCES_UTIL})
add_library(VIR SHARED ${SOURCES_VIR})
add_library(BIR SHARED ${SOURCES_BIR})
add_library(Schedule SHARED ${SOURCES_SCHEDULE})
add_executable(exec ${SOURCES_EXEC})
target_link_libraries(exec Schedule BIR VIR Util ${Boost_LIBRARIES} ${GECODE_LIBRARIES} ${PROJECT_LINK_LIBS})

