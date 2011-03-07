set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# External libraries.
add_subdirectory(tinyxml)
if(WIN32)
  add_subdirectory(dxsdk/200806/Samples/C++/DXUT/Core)
endif()

# The OBOY library.
add_subdirectory(OBoyLib)
add_subdirectory(OBoy)