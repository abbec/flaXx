if (WIN32)
  set(SDL_SRC
	src/SDL.c
	src/events/SDL_active.c
	src/audio/SDL_audio.c
	src/audio/SDL_audiocvt.c
	src/video/SDL_blit.c
	src/video/SDL_blit_0.c
	src/video/SDL_blit_1.c
	src/video/SDL_blit_A.c
	src/video/SDL_blit_N.c
	src/video/SDL_bmp.c
	src/cdrom/SDL_cdrom.c
	src/cpuinfo/SDL_cpuinfo.c
	src/video/SDL_cursor.c
	src/audio/windib/SDL_dibaudio.c
	src/video/windib/SDL_dibevents.c
	src/video/windib/SDL_dibvideo.c
	src/audio/disk/SDL_diskaudio.c
	src/audio/dummy/SDL_dummyaudio.c
	src/audio/windx5/SDL_dx5audio.c
	src/video/Windx5/SDL_dx5events.c
	src/video/Windx5/SDL_dx5video.c
	src/video/windx5/SDL_dx5yuv.c
	src/SDL_error.c
	src/events/SDL_events.c
	src/events/SDL_expose.c
	src/SDL_fatal.c
	src/video/SDL_gamma.c
	src/stdlib/SDL_getenv.c
	src/stdlib/SDL_iconv.c
	src/joystick/SDL_joystick.c
	src/events/SDL_keyboard.c
	src/stdlib/SDL_malloc.c
	src/audio/SDL_mixer.c
	src/audio/SDL_mixer_MMX_VC.c
	src/joystick/win32/SDL_mmjoystick.c
	src/events/SDL_mouse.c
	src/video/dummy/SDL_nullevents.c
	src/video/dummy/SDL_nullmouse.c
	src/video/dummy/SDL_nullvideo.c
	src/video/SDL_pixels.c
	src/stdlib/SDL_qsort.c
	src/events/SDL_quit.c
	src/events/SDL_resize.c
	src/video/SDL_RLEaccel.c
	src/file/SDL_rwops.c
	src/stdlib/SDL_stdlib.c
	src/video/SDL_stretch.c
	src/stdlib/SDL_string.c
	src/video/SDL_surface.c
	src/cdrom/win32/SDL_syscdrom.c
	src/thread/generic/SDL_syscond.c
	src/video/wincommon/SDL_sysevents.c
	src/loadso/win32/SDL_sysloadso.c
	src/video/wincommon/SDL_sysmouse.c
	src/thread/win32/SDL_sysmutex.c
	src/thread/win32/SDL_syssem.c
	src/thread/win32/SDL_systhread.c
	src/timer/win32/SDL_systimer.c
	src/video/wincommon/SDL_syswm.c
	src/thread/SDL_thread.c
	src/timer/SDL_timer.c
	src/video/SDL_video.c
	src/audio/SDL_wave.c
	src/video/wincommon/SDL_wingl.c
	src/video/SDL_yuv.c
	src/video/SDL_yuv_sw.c)

  set(SDL_MAIN_SRC
	src/main/win32/SDL_win32_main.c
	)

endif(WIN32)

add_library(SDL STATIC ${SDL_SRC})



  
  if (MSVC)
	target_link_libraries(SDL winmm.lib)
	find_package(DXGuid)
	if (DXGUID_FOUND)
	  target_link_libraries(SDL ${DXGUID_LIBRARIES})
	else (DXGUID_FOUND)
	  message(FATAL_ERROR "DXGUID not found!")
	endif(DXGUID_FOUND)
  else(MSVC)
	target_link_libraries(SDL winmm)
	target_link_libraries(SDL dxguid)
  endif(MSVC)

endif(WIN32)

add_library(SDLMain STATIC ${SDL_MAIN_SRC})
