# asteroid

add_definitions( -D_CONSOLE -DOBOY_PLATFORM_LINUX -D_UNICODE -DUNICODE )
add_definitions( "/W3 /wd4995 /nologo" )

include_directories( ${OBoy_SOURCE_DIR}/libs )

link_directories(
  ${IRRKLANG_LIBRARY_DIR}
  ${CEGUI_LIBRARY_DIR}
  ${GLEW_LIBRARY_DIR}
)

if(WIN32)
  include_directories ( ${DXSDK_LIBRARY_DIR} )
endif()

set(demo2_SRCS
  Body.cpp
  Demo2.cpp
  Explosion.cpp
  main.cpp
)
set(demo2_HDRS
  Body.h
  Demo2.h
  Explosion.h
)

add_executable(Demo2 ${demo2_SRCS} ${demo2_HDRS})

target_link_libraries(Demo2
  OBoy
  OBoyLib
  tinyxml
  irrKlang
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${CEGUI_LIBRARIES}
  ${CEGUI_OPENGL_LIBRARIES}
  ${GLEW_LIBRARY}
)

if(WIN32)
target_link_libraries(Demo2
  d3dx9
  DxErr9
  DXUT
  ${CEGUI_DIRECT3D9_LIBRARIES}
)
endif()

if(MSVC)
	# These are used to create visual studio folders.
	source_group("" FILES ${demo2_SRCS} ${demo2_HDRS})
endif()