add_subdirectory(zlib)
add_subdirectory(libpng)

if (WIN32)
	add_subdirectory(sdl)
endif()


if (X64_BUILD)
	if(WIN32)
  		set_target_properties(zlib png SDL SDLMain PROPERTIES SUFFIX ".x64${CMAKE_STATIC_LIBRARY_SUFFIX}" FOLDER "External")
  	else()
  		set_target_properties(zlib png PROPERTIES SUFFIX ".x64${CMAKE_STATIC_LIBRARY_SUFFIX}" FOLDER "External")
  	endif()
endif()