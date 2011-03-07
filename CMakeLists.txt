cmake_minimum_required(VERSION 2.6)

project(OBoy)

if(UNIX)
	set(OBOY_INSTALL_BY_DEFAULT ON)
else(UNIX)
	set(OBOY_INSTALL_BY_DEFAULT OFF)
endif(UNIX)

option(OBOY_INSTALL "Install OBoy libs, includes, and CMake scripts" ${OBOY_INSTALL_BY_DEFAULT})
#option(OBOY_INSTALL_DOC "Install OBoy documentation" OFF)
option(OBOY_BUILD_SHARED "Build OBoy shared libraries" OFF)
option(OBOY_BUILD_STATIC "Build OBoy static libraries" ON)
option(OBOY_BUILD_EXAMPLES "Build OBoy examples" ON)
option(OBOY_BUILD_MACROWARS "Build Macrowars" ON)

set(OBOY_VERSION 1.0)

# dependencies.
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

set(CEGUI_DIR ${OBoy_SOURCE_DIR}/libs/CEGUI-0.7.5 CACHE PATH "CEGUI SDK directory")
set(CEGUI_INCLUDE_DIR ${CEGUI_DIR}/cegui/include)
set(CEGUI_LIBRARY_DIR ${CEGUI_DIR}/lib)
set(CEGUI_LIBRARIES
  debug CEGUIBase_d
  debug CEGUIExpatParser_d
  optimized CEGUIBase
  optimized CEGUIExpatParser
)
set(CEGUI_OPENGL_LIBRARIES debug CEGUIOpenGLRenderer_d optimized CEGUIOpenGLRenderer)
set(CEGUI_D3D9_LIBRARIES debug CEGUIDirect3D9Renderer_d optimized CEGUIDirect3D9Renderer)

set(IRRKLANG_INCLUDE_DIR ${OBoy_SOURCE_DIR}/libs/irrKlang-1.3.0/include)
set(IRRKLANG_LIBRARY_DIR ${OBoy_SOURCE_DIR}/libs/irrKlang-1.3.0/lib/Win32-visualStudio)

set(GLEW_INCLUDE_DIR ${OBoy_SOURCE_DIR}/libs/glew/include)
set(GLEW_LIBRARY_DIR ${OBoy_SOURCE_DIR}/libs/glew/lib)
set(GLEW_LIBRARY glew32)

if(WIN32)
  set(DXSDK_INCLUDE_DIR ${OBoy_SOURCE_DIR}/libs/dxsdk/200806/Include)
  set(DXSDK_LIBRARY_DIR ${OBoy_SOURCE_DIR}/libs/dxsdk/200806/Lib/x86)

  set(DXUT_INCLUDE_DIR ${OBoy_SOURCE_DIR}/libs/dxsdk/200806/Samples/C++/DXUT/Core)
endif()

# The OBOY library.
add_subdirectory(libs)

if(OBOY_BUILD_EXAMPLES)
  # gamepad example.
  add_subdirectory(demo1)
  # asteroid example.
  add_subdirectory(demo2)
endif(OBOY_BUILD_EXAMPLES)

if(OBOY_BUILD_MACROWARS)
  add_subdirectory(macrowars)
endif(OBOY_BUILD_MACROWARS)

#if(OBOY_INSTALL_DOC)
#  install(DIRECTORY Documentation DESTINATION share/doc/OBOY)
#endif(OBOY_INSTALL_DOC)