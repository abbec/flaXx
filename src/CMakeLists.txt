set (FLAXX_SRC
main.cpp
app/flaXxMain.cpp
math/montecarlo.cpp
math/vector3f.cpp
object/diffuse.cpp
object/cooktorrance.cpp
object/blinnphong.cpp
object/plane.cpp
object/sphere.cpp
render/imageplane.cpp
render/render.cpp
scene/scene.cpp
scene/camera.cpp
util/commandLineParser.cpp
util/options.cpp)


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

add_executable(tests/i_test ${INTER_TEST_SRC})

add_executable(tests/random_test ${RANDOM_TEST_SRC})

add_executable(tests/xml_test ${XML_TEST_SRC})

# Skapa exekerbar fil
add_executable(flaXx ${FLAXX_SRC})

# Länka med SDL
TARGET_LINK_LIBRARIES(flaXx ${SDL_LIBRARY} ${PNG_LIBRARY}) 