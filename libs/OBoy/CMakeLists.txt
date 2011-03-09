add_definitions( -D_CONSOLE -DOBOY_PLATFORM_LINUX -D_UNICODE -DUNICODE )
add_definitions( "/W3 /wd4005 /wd4996 /nologo" )

include_directories (
  ../
  ${SDL_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
  ${CEGUI_INCLUDE_DIR}
  ${IRRKLANG_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
)

if(WIN32)
  include_directories (
    ${DXSDK_INCLUDE_DIR}
    ${DXUT_INCLUDE_DIR}
  )
endif()

set(OBoy_controllers_SRCS
  Controller.cpp
  GamePad.cpp
  Keyboard.cpp
  Mouse.cpp
)
set(OBoy_controllers_HDRS
  Controller.h
  GamePad.h
  GamePadListener.h
  Keyboard.h
  KeyboardListener.h
  Mouse.h
  MouseListener.h
)
set(OBoy_gui_SRCS
  Gui.cpp
  #GuiSubscriberSlot.cpp
)
set(OBoy_gui_HDRS
  Gui.h
  #GuiEvent.h
  #GuiEventArgs.h
  #GuiFunctorCopySlot.h
  #GuiFunctorPointerSlot.h
  #GuiFunctorReferenceBinder
  #GuiFunctorReferenceSlot.h
  #GuiMemberFunctionSlot.h
  #GuiSlotFunctorBase.h
  #GuiSubscriberSlot.h
  #GuiWindow.h
)
set(OBoy_noise_SRCS
  CoherentNoise.cpp
  noiseutils.cpp
  #complexplanet.cpp
  #texturegranite.cpp
  #texturejade.cpp
  #texturesky.cpp
  #textureslime.cpp
  #texturewood.cpp
)
set(OBoy_noise_HDRS
  CoherentNoise.h
  noiseutils.h
)
set(OBoy_shapes_HDRS
  Cube.h
  LineStrip.h
  Lines.h
  Sphere.h
  Texturable.h
  Torus.h
  TriStrip.h
)
set(OBoy_linux_SRCS
  LinuxEnvironment.cpp
  LinuxGLInterface.cpp
  LinuxGamePad.cpp
  LinuxGraphics.cpp
  LinuxGui.cpp
  LinuxImage.cpp
  LinuxImageDataLoader.cpp
  LinuxPersistenceLayer.cpp
  LinuxPlane.cpp
  LinuxResourceLoader.cpp
  LinuxResourceSaver.cpp
  LinuxSound.cpp
  LinuxSoundPlayer.cpp
  LinuxSphere.cpp
  LinuxStorage.cpp
)
set(OBoy_linuxshapes_SRCS
  LinuxCube.cpp
  LinuxLineStrip.cpp
  LinuxLines.cpp
  LinuxShape.cpp
  LinuxTorus.cpp
  LinuxTriStrip.cpp
)
set(OBoy_linux_HDRS
  LinuxEnvironment.h
  LinuxGLInterface.h
  LinuxGamePad.h
  LinuxGraphics.h
  LinuxGui.h
  LinuxImage.h
  LinuxImageDataLoader.h
  LinuxPersistenceLayer.h
  LinuxResourceLoader.h
  LinuxResourceSaver.h
  LinuxSound.h
  LinuxSoundPlayer.h
  LinuxStorage.h
)
set(OBoy_linuxshapes_HDRS
  LinuxCube.h
  LinuxLineStrip.h
  LinuxLines.h
  LinuxPlane.h
  LinuxShape.h
  LinuxSphere.h
  LinuxTorus.h
  LinuxTriStrip.h
)
set(OBoy_windows_SRCS
  AES.cpp
  Crypto.cpp
  #CryptoWii.cpp
  WinD3DInterface.cpp
  WinEnvironment.cpp
  WinGamePad.cpp
  WinGraphics.cpp
  WinGui.cpp
  WinImage.cpp
  WinPersistenceLayer.cpp
  WinResourceLoader.cpp
  WinResourceSaver.cpp
  WinSound.cpp
  WinSoundPlayer.cpp
  WinStorage.cpp
)
set(OBoy_winshapes_SRCS
  WinCube.cpp
  WinLineStrip.cpp
  WinLines.cpp
  WinSphere.cpp
  WinTriStrip.cpp
)
set(OBoy_windows_HDRS
  AES.h
  Crypto.h
  WinD3DInterface.h
  WinEnvironment.h
  WinGamePad.h
  WinGraphics.h
  WinGui.h
  WinImage.h
  WinPersistenceLayer.h
  WinResourceLoader.h
  WinResourceSaver.h
  WinSound.h
  WinSoundPlayer.h
  WinStorage.h
)
set(OBoy_winshapes_HDRS
  WinCube.h
  WinLineStrip.h
  WinLines.h
  WinSphere.h
  WinTriStrip.h
)
set(OBoy_general_SRCS
  Environment.cpp
  Font.cpp
  #MMMem.cpp
  #PopCapFont.cpp
  Resource.cpp
  ResourceGroup.cpp
  ResourceManager.cpp
  Storage.cpp
)
set(OBoy_general_HDRS
  Environment.h
  Font.h
  Game.h
  Graphics.h
  Image.h
  #MMMem.h
  PersistenceLayer.h
  PopCapFont.h
  Resource.h
  ResourceGroup.h
  ResourceLoader.h
  ResourceManager.h
  ResourceSaver.h
  Sound.h
  SoundPlayer.h
  Storage.h
  Util.h   
)

if(OBOY_BUILD_SHARED)
	add_library(OBoy_shared SHARED
		${OBoy_general_HDRS}
    ${OBoy_general_SRCS}
		${OBoy_controllers_SRCS}
		${OBoy_controllers_HDRS}
		${OBoy_gui_SRCS}
		${OBoy_gui_HDRS}
		${OBoy_noise_SRCS}
		${OBoy_noise_HDRS}
		${OBoy_shapes_HDRS}
		${OBoy_linux_SRCS}
		${OBoy_linux_HDRS}
    ${OBoy_linuxshapes_SRCS}
    ${OBoy_linuxshapes_HDRS}
		${OBoy_windows_SRCS}
		${OBoy_windows_HDRS}
    ${OBoy_winshapes_SRCS}
		${OBoy_winshapes_HDRS}
	)
	set_target_properties(OBoy_shared PROPERTIES
		OUTPUT_NAME "OBoy"
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
		VERSION ${OBOY_VERSION}
	)
endif()

if(OBOY_BUILD_STATIC)
	add_library(OBoy STATIC
		${OBoy_general_HDRS}
    ${OBoy_general_SRCS}
		${OBoy_controllers_SRCS}
		${OBoy_controllers_HDRS}
		${OBoy_gui_SRCS}
		${OBoy_gui_HDRS}
		${OBoy_noise_SRCS}
		${OBoy_noise_HDRS}
		${OBoy_shapes_HDRS}
		${OBoy_linux_SRCS}
		${OBoy_linux_HDRS}
    ${OBoy_linuxshapes_SRCS}
    ${OBoy_linuxshapes_HDRS}
		${OBoy_windows_SRCS}
		${OBoy_windows_HDRS}
    ${OBoy_winshapes_SRCS}
		${OBoy_winshapes_HDRS}
	)
	set_target_properties(OBoy PROPERTIES
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
		VERSION ${OBOY_VERSION}
	)
endif()

if(MSVC)
	# These are used to create visual studio folders.
	source_group(controllers FILES ${OBoy_controllers_SRCS} ${OBoy_controllers_HDRS})
	source_group(gui FILES ${OBoy_gui_SRCS} ${OBoy_gui_HDRS})
  source_group(noise FILES ${OBoy_noise_SRCS} ${OBoy_noise_HDRS})
  source_group(shapes FILES ${OBoy_shapes_HDRS})
  source_group(linux FILES ${OBoy_linux_SRCS} ${OBoy_linux_HDRS})
  source_group(linux\\shapes FILES ${OBoy_linuxshapes_SRCS} ${OBoy_linuxshapes_HDRS})
  source_group(windows FILES ${OBoy_windows_SRCS} ${OBoy_windows_HDRS})
  source_group(windows\\shapes FILES ${OBoy_winshapes_SRCS} ${OBoy_winshapes_HDRS})
	source_group("" FILES ${OBoy_general_SRCS} ${OBoy_general_HDRS})
endif()

if(OBOY_INSTALL)
	# install headers
	install(FILES ${OBoy_general_HDRS} DESTINATION include/OBoy)
	install(FILES ${OBoy_controllers_HDRS} DESTINATION include/OBoy)
	install(FILES ${OBoy_gui_HDRS} DESTINATION include/OBoy)
	install(FILES ${OBoy_noise_HDRS} DESTINATION include/OBoy)
	install(FILES ${OBoy_shapes_HDRS} DESTINATION include/OBoy)
	install(FILES ${OBoy_linux_HDRS} DESTINATION include/OBoy)
  install(FILES ${OBoy_linuxshapes_HDRS} DESTINATION include/OBoy)
	install(FILES ${OBoy_windows_HDRS} DESTINATION include/OBoy)
  install(FILES ${OBoy_winshapes_HDRS} DESTINATION include/OBoy)

	# install libraries
	if(OBOY_BUILD_SHARED)
		install(TARGETS OBoy_shared EXPORT OBoy-targets DESTINATION lib)
	endif()
	if(OBOY_BUILD_STATIC)
		install(TARGETS OBoy EXPORT OBoy-targets DESTINATION lib)
	endif()

	# install build system hooks for third-party apps
	install(EXPORT OBoy-targets DESTINATION lib/OBoy)
	install(FILES OBoyConfig.cmake DESTINATION lib/OBoy)
endif(OBOY_INSTALL)