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

set(demo1_SRCS
  Demo1.cpp
  main.cpp
)
set(demo1_HDRS
  Demo1.h
)

add_executable(Demo1 ${demo1_SRCS} ${demo1_HDRS})

target_link_libraries(Demo1
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
target_link_libraries(Demo1
  d3dx9
  DxErr9
  DXUT
  ${CEGUI_DIRECT3D9_LIBRARIES}
)
endif()

if(MSVC)
	# These are used to create visual studio folders.
	source_group("" FILES ${demo1_SRCS} ${demo1_HDRS})
endif()