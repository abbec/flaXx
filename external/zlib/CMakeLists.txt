set(ZLIB_SRC
  src/adler32.c
  src/compress.c
  src/crc32.c
  src/crc32.h
  src/deflate.c
  src/deflate.h
  src/gzclose.c
  src/gzguts.h
  src/gzlib.c
  src/gzread.c
  src/gzwrite.c
  src/infback.c
  src/inffast.c
  src/inffast.h
  src/inffixed.h
  src/inflate.c
  src/inflate.h
  src/inftrees.c
  src/inftrees.h
  src/trees.c
  src/trees.h
  src/uncompr.c
  src/zconf.h
  src/zlib.h
  src/zutil.c
  src/zutil.h)

if(MSVC)
  # Ignore warning C4013 under MSVC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4013")
endif(MSVC)

add_library(zlib STATIC ${ZLIB_SRC})
