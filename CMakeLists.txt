cmake_minimum_required(VERSION 3.14)

project(KVPStorage)

# C++17 so can work with C++20
set(CMAKE_CXX_STANDARD 17)

include_directories(src tst lib/nlohmann)

# set(DCMAKE_BUILD_TYPE,Debug)

add_subdirectory(src)
add_subdirectory(tst)

#set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Build options: Debug Release Coverage." FORCE)

# Use generator expression to enable flags for the Coverage profile
# target_compile_options(KVPStorage PUBLIC "--coverage")
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")