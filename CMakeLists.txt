cmake_minimum_required (VERSION 2.8)
project (flaXx)

set (CMAKE_INCLUDE_CURRENT_DIR TRUE)

FIND_PACKAGE(SDL) 
     
IF(SDL_FOUND) 
  INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
ELSE(SDL_FOUND) 
  MESSAGE(STATUS "Hittade inte SDL.")  
ENDIF(SDL_FOUND) 

# The version number.
set (FLAXX_VERSION_MAJOR 0)
set (FLAXX_VERSION_MINOR 1)

add_subdirectory (src)