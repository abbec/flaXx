set(LIBPNG_SRC
src/png.c
src/png.h
src/pngconf.h
src/pngdebug.h
src/pngerror.c
src/pngget.c
src/pnginfo.h
src/pngmem.c
src/pngpread.c
src/pngpriv.h
src/pngread.c
src/pngrio.c
src/pngrtran.c
src/pngrutil.c
src/pngset.c
src/pngstruct.h
src/pngtrans.c
src/pngwio.c
src/pngwrite.c
src/pngwtran.c
src/pngwutil.c)

add_library(png STATIC ${LIBPNG_SRC})
target_link_libraries(png zlib)
