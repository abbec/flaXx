set (FLAXX_SRC
main.cpp
app/flaXxMain.cpp
render/render.cpp
util/commandLineParser.cpp
util/options.cpp)

# Skapa exekerbar fil
add_executable(flaXx ${FLAXX_SRC})

# Länka med SDL

TARGET_LINK_LIBRARIES(flaXx ${SDL_LIBRARY}) 