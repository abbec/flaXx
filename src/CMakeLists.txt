set (FLAXX_SRC
main.cpp
app/flaXxMain.h
app/flaXxMain.cpp
math/montecarlo.h
math/montecarlo.cpp
math/vector3f.h
math/vector3f.cpp
object/object.h
object/diffuse.h
object/diffuse.cpp
object/cooktorrance.h
object/cooktorrance.cpp
object/blinnphong.cpp
object/plane.cpp
object/sphere.cpp
render/imageplane.cpp
render/render.cpp
scene/scene.cpp
scene/camera.cpp
util/commandLineParser.cpp
util/options.cpp
object/blinnphong.h
object/plane.h
object/sphere.h
render/imageplane.h
render/render.h
scene/scene.h
scene/camera.h
util/commandLineParser.h
util/options.h)

# Groups in IDE
source_group("" FILES ${FLAXX_SRC})

source_group("Math" FILES 
  math/montecarlo.h 
  math/montecarlo.cpp
  math/vector3f.h
  math/vector3f.cpp)

source_group("App" FILES
  app/flaXxMain.h
  app/flaXxMain.cpp)

source_group("Object" FILES
  object/object.h
  object/diffuse.h
  object/diffuse.cpp
  object/cooktorrance.h
  object/cooktorrance.cpp
  object/blinnphong.h
  object/blinnphong.cpp
  object/plane.h
  object/plane.cpp
  object/sphere.h
  object/sphere.cpp
  )

source_group("Render" FILES
  render/imageplane.h
  render/imageplane.cpp
  render/render.h
  render/render.cpp)

source_group("Scene" FILES
  scene/scene.h
  scene/scene.cpp
  scene/camera.h
  scene/camera.cpp
)

source_group("Util" FILES
  util/commandLineParser.h
  util/commandLineParser.cpp
  util/options.h
  util/options.cpp
)

set(INTER_TEST_SRC
tests/intersection_test.cpp
object/sphere.cpp
object/plane.cpp
math/vector3f.cpp)


set(RANDOM_TEST_SRC
tests/random_test.cpp
math/montecarlo.cpp
math/vector3f.cpp)

set(XML_TEST_SRC
tests/xml_test.cpp
util/xmlParser.cpp
scene/camera.cpp)

# Needed for M_PI
if(MSVC)
  add_definitions(-D_USE_MATH_DEFINES)
endif(MSVC)

# Tests
add_executable(i_test ${INTER_TEST_SRC})
add_executable(random_test ${RANDOM_TEST_SRC})
add_executable(xml_test ${XML_TEST_SRC})

# Main executable
add_executable(flaXx ${FLAXX_SRC})

# Link SDL
if (MSVC)
  target_link_libraries(flaXx SDLMain SDL png)
elseif(MINGW)
  target_link_libraries(flaXx mingw32 SDL SDLMain png)
endif(MSVC)

# Add x64 to executable
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set_target_properties(flaXx PROPERTIES SUFFIX ".x64${CMAKE_EXECUTABLE_SUFFIX}")
endif()

# Put in tests folder in IDE
set_target_properties(i_test random_test xml_test PROPERTIES FOLDER "Tests")