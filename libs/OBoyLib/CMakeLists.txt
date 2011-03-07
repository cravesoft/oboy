add_definitions( -D_CONSOLE -DOBOY_PLATFORM_LINUX -D_UNICODE -DUNICODE )
add_definitions( "/W3 /wd4996 /nologo" )

set(OBoyLib_boundary_SRCS
  Circle.cpp
  HeightBoundary.cpp
  IntersectionBoundary.cpp
  Rect.cpp
)
set(OBoyLib_boundary_HDRS
  Boundary.h
  Circle.h
  HeightBoundary.h
  IntersectionBoundary.h
  Rect.h
)
set(OBoyLib_function_SRCS
  SinFunction2D.cpp
  SmoothTransitionFunction.cpp
)
set(OBoyLib_function_HDRS
  Function.h
  Function2D.h
  SinFunction2D.h
  SmoothTransitionFunction.h
)
set(OBoyLib_md5_SRCS
  md5.c
)
set(OBoyLib_md5_HDRS
  md5.h
)
set(OBoyLib_messenger_SRCS
  Messenger.cpp
)
set(OBoyLib_messenger_HDRS
  MessageListener.h
  MessageSource.h
  Messenger.h
)
set(OBoyLib_perf_SRCS
  PerfTimer.cpp
)
set(OBoyLib_perf_HDRS
  PerfTimer.h
)
set(OBoyLib_tickable_SRCS
  ReusableTickableQueue.cpp
  ReusableTickableSet.cpp
  TickableQueue.cpp
  TickableSet.cpp
)
set(OBoyLib_tickable_HDRS
  ReusableTickable.h
  ReusableTickableQueue.h
  ReusableTickableSet.h
  Tickable.h
  TickableQueue.h
  TickableSet.h
)
set(OBoyLib_unicode_SRCS
  UString.cpp
  UStringStream.cpp
)
set(OBoyLib_unicode_HDRS
  UString.h
  UStringStream.h
)
set(OBoyLib_general_SRCS
  Clipboard.cpp
  MemDbg.cpp
  Positionable.cpp
)
set(OBoyLib_general_HDRS
  Clipboard.h
  Cloneable.h
  Color.h
  CrtDbgInc.h
  CrtDbgNew.h
  MemDbg.h
  OBoyMath.h
  OBoyUtil.h
  Positionable.h
  Vector2.h
  Vector3.h
)

if(OBOY_BUILD_SHARED)
	add_library(OBoyLib_shared SHARED
		${OBoyLib_general_HDRS}
    ${OBoyLib_general_SRCS}
		${OBoyLib_boundary_SRCS}
		${OBoyLib_boundary_HDRS}
		${OBoyLib_function_SRCS}
		${OBoyLib_function_HDRS}
		${OBoyLib_md5_SRCS}
		${OBoyLib_md5_HDRS}
		${OBoyLib_messenger_SRCS}
		${OBoyLib_messenger_HDRS}
		${OBoyLib_perf_SRCS}
		${OBoyLib_perf_HDRS}
		${OBoyLib_tickable_SRCS}
		${OBoyLib_tickable_HDRS}
    ${OBoyLib_unicode_SRCS}
		${OBoyLib_unicode_HDRS}
	)
	set_target_properties(OBoyLib_shared PROPERTIES
		OUTPUT_NAME "OBoyLib"
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
		VERSION ${OBOY_VERSION}
	)
endif()

if(OBOY_BUILD_STATIC)
	add_library(OBoyLib STATIC
		${OBoyLib_general_HDRS}
    ${OBoyLib_general_SRCS}
		${OBoyLib_boundary_SRCS}
		${OBoyLib_boundary_HDRS}
		${OBoyLib_function_SRCS}
		${OBoyLib_function_HDRS}
		${OBoyLib_md5_SRCS}
		${OBoyLib_md5_HDRS}
		${OBoyLib_messenger_SRCS}
		${OBoyLib_messenger_HDRS}
		${OBoyLib_perf_SRCS}
		${OBoyLib_perf_HDRS}
		${OBoyLib_tickable_SRCS}
		${OBoyLib_tickable_HDRS}
    ${OBoyLib_unicode_SRCS}
		${OBoyLib_unicode_HDRS}
	)
	set_target_properties(OBoyLib PROPERTIES
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
		VERSION ${OBOY_VERSION}
	)
endif()

if(MSVC)
	# These are used to create visual studio folders.
	source_group(boundary FILES ${OBoyLib_boundary_SRCS} ${OBoyLib_boundary_HDRS})
	source_group(function FILES ${OBoyLib_function_SRCS} ${OBoyLib_function_HDRS})
  source_group(md5 FILES ${OBoyLib_md5_SRCS} ${OBoyLib_md5_HDRS})
  source_group(messenger FILES ${OBoyLib_messenger_SRCS} ${OBoyLib_messenger_HDRS})
  source_group(perf FILES ${OBoyLib_perf_SRCS} ${OBoyLib_perf_HDRS})
  source_group(tickable FILES ${OBoyLib_tickable_SRCS} ${OBoyLib_tickable_HDRS})
  source_group(unicode FILES ${OBoyLib_unicode_SRCS} ${OBoyLib_unicode_HDRS})
	source_group("" FILES ${OBoyLib_general_SRCS} ${OBoyLib_general_HDRS})
endif()

if(OBOY_INSTALL)
	# install headers
	install(FILES ${OBoyLib_general_HDRS} DESTINATION include/OBoyLib)
	install(FILES ${OBoyLib_boundary_HDRS} DESTINATION include/OBoyLib)
	install(FILES ${OBoyLib_function_HDRS} DESTINATION include/OBoyLib)
	install(FILES ${OBoyLib_md5_HDRS} DESTINATION include/OBoyLib)
	install(FILES ${OBoyLib_messenger_HDRS} DESTINATION include/OBoyLib)
	install(FILES ${OBoyLib_perf_HDRS} DESTINATION include/OBoyLib)
	install(FILES ${OBoyLib_tickable_HDRS} DESTINATION include/OBoyLib)
  install(FILES ${OBoyLib_unicode_HDRS} DESTINATION include/OBoyLib)

	# install libraries
	if(OBOY_BUILD_SHARED)
		install(TARGETS OBoyLib_shared EXPORT OBoyLib-targets DESTINATION lib)
	endif()
	if(OBOY_BUILD_STATIC)
		install(TARGETS OBoyLib EXPORT OBoyLib-targets DESTINATION lib)
	endif()

	# install build system hooks for third-party apps
	install(EXPORT OBoyLib-targets DESTINATION lib/OBoyLib)
	install(FILES OBoyLibConfig.cmake DESTINATION lib/OBoyLib)
endif(OBOY_INSTALL)