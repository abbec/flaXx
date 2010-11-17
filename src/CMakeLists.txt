set (FLAXX_SRC
main.cpp
app/flaXxMain.cpp
math/montecarlo.cpp
math/vector3f.cpp
object/diffuse.cpp
object/plane.cpp
object/sphere.cpp
render/imageplane.cpp
render/render.cpp
scene/scene.cpp
scene/camera.cpp
util/commandLineParser.cpp
util/options.cpp)

# Skapa exekerbar fil
add_executable(flaXx ${FLAXX_SRC})

# Länka med SDL
TARGET_LINK_LIBRARIES(flaXx ${SDL_LIBRARY}) 