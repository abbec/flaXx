cmake_minimum_required (VERSION 2.8)
project (flaXx)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Detect 32/64 bits
set(X64_BUILD FALSE)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(X64_BUILD TRUE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Include directories
if(WIN32)
include_directories("external/sdl/include")
endif()

include_directories("external/zlib/src" "external/libpng/src")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# The version number.
set (FLAXX_VERSION_MAJOR 0)
set (FLAXX_VERSION_MINOR 1)

add_subdirectory(external)

# Treat warnings as errors (not for external projects)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
elseif(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif(MSVC)

add_subdirectory(src)
