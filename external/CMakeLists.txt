add_subdirectory(zlib)
add_subdirectory(libpng)
add_subdirectory(sdl)


if (X64_BUILD)
  set_target_properties(zlib png SDL SDLMain PROPERTIES SUFFIX ".x64${CMAKE_STATIC_LIBRARY_SUFFIX}" FOLDER "External")
endif()