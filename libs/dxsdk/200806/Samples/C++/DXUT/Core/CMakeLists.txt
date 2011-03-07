#cmake_minimum_required(VERSION 2.6)

#project(DXUT)

add_definitions( -D_CONSOLE -DOBOY_PLATFORM_LINUX -D_UNICODE -DUNICODE -D_LIB)
add_definitions( "/W3 /wd4005 /wd4996 /nologo" )

#-D_CRTDBG_MAP_ALLOC
#D3D_DEBUG_INFO

include_directories ( ../../../../Include )

set(DXUT_SRCS
  DXUT.cpp
  DXUTenum.cpp
  DXUTmisc.cpp
)
set(DXUT_HDRS
  DXUT.h
  DXUTenum.h
  DXUTmisc.h
)

if(OBOY_BUILD_SHARED)
	add_library(DXUT_shared SHARED
		${DXUT_HDRS}
    ${DXUT_SRCS}
	)
	set_target_properties(DXUT_shared PROPERTIES
		OUTPUT_NAME "DXUT"
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
	)
endif()

if(OBOY_BUILD_STATIC)
	add_library(DXUT STATIC
		${DXUT_HDRS}
    ${DXUT_SRCS}
	)
	set_target_properties(DXUT PROPERTIES
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
	)
endif()

if(MSVC)
	# These are used to create visual studio folders.
	source_group("" FILES ${DXUT_SRCS} ${DXUT_HDRS})
endif()