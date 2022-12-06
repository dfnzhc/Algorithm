cmake_minimum_required(VERSION 3.23)

project(AlgorithmTest VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (MSVC)
    list(APPEND _DEFINITIONS "_CRT_SECURE_NO_WARNINGS")
    list(APPEND _DEFINITIONS "_ENABLE_EXTENDED_ALIGNED_STORAGE")
endif ()

if (WIN32)
    list(APPEND _DEFINITIONS "GLAD_GLAPI_EXPORT" "NOMINMAX" "WIN32_LEAN_AND_MEAN")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif (WIN32)

set(TEST_SOURCES
        DataStructures/SparseTable/SparseTable.cpp
        )

set(PCH
        <iostream>
        <memory>
        <utility>
        <algorithm>
        <functional>
        <fstream>
        <execution>
        <filesystem>
        <string>
        <sstream>
        <unordered_map>
        <unordered_set>
        <stdexcept>
        <queue>
        <stack>
        <array>
        <numeric>
        <map>
        <wrl.h>
        <limits>
        <set>
        <span>
        <vector>
        <cmath>
        )

foreach (file ${TEST_SOURCES})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${CMAKE_CURRENT_SOURCE_DIR}/${file})

    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_definitions(${name} PRIVATE ${_DEFINITIONS})
    target_precompile_headers(${name} PRIVATE ${PCH})
    set_property(TARGET ${name} PROPERTY CXX_STANDARD 23)
    set_target_properties(${name} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
    add_test("${name}_test" ${name})
endforeach ()
