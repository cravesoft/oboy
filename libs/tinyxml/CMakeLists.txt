add_definitions( -D_UNICODE -DUNICODE )

set(tinyxml_SRCS
  tinystr.cpp
  tinyxml.cpp
  tinyxmlerror.cpp
  tinyxmlparser.cpp
)
set(tinyxml_HDRS
  tinystr.h
  tinyxml.h
)

if(OBOY_BUILD_SHARED)
	add_library(tinyxml_shared SHARED
	${tinyxml_SRCS}
  ${tinyxml_HDRS}
	)
	set_target_properties(tinyxml_shared PROPERTIES
		OUTPUT_NAME "tinyxml"
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
	)
endif()

if(OBOY_BUILD_STATIC)
	add_library(tinyxml STATIC
	${tinyxml_SRCS}
  ${tinyxml_HDRS}
	)
	set_target_properties(tinyxml PROPERTIES
		CLEAN_DIRECT_OUTPUT 1
    FOLDER "Libs"
	)
endif()

if(MSVC)
	# These are used to create visual studio folders.
	source_group("" FILES ${tinyxml_SRCS} ${tinyxml_HDRS})
endif()