################################################################################
### $Id: CMakeLists.txt 9596 2015-02-01 09:41:54Z marcus $
################################################################################

FIND_PACKAGE(BZip2 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Gettext REQUIRED)
FIND_PACKAGE(Boost REQUIRED)

################################################################################

INCLUDE_DIRECTORIES(
					"${CMAKE_SOURCE_DIR}/liblobby/src/"
					"${CMAKE_SOURCE_DIR}/libutil/src/"
					"${CMAKE_SOURCE_DIR}/mygettext/src/"
					"${CMAKE_SOURCE_DIR}/libsiedler2/src/"
					"${CMAKE_SOURCE_DIR}/libendian/src/"
					"${CMAKE_SOURCE_DIR}/src"
					${BZIP2_INCLUDE_DIR}
					${Boost_INCLUDE_DIR}
					)

LINK_DIRECTORIES("${CMAKE_SOURCE_DIR}/libsiedler2/src" "${CMAKE_SOURCE_DIR}/mygettext/src" "${CMAKE_SOURCE_DIR}/libutil/src" "${CMAKE_SOURCE_DIR}/liblobby/src" "${CMAKE_SOURCE_DIR}/libendian/src")

################################################################################

FILE(GLOB SOURCES_OTHER *.cpp *.h)
SOURCE_GROUP(other FILES ${SOURCES_OTHER})

SET(SOURCES_SUBDIRS )
MACRO(AddDirectory dir)
	FILE(GLOB SUB_FILES ${dir}/*.cpp ${dir}/*.h)
	SET(SOURCES_SUBDIRS ${SOURCES_SUBDIRS} ${SUB_FILES})
	SOURCE_GROUP(${dir} FILES ${SUB_FILES})
ENDMACRO()

AddDirectory(addons)
AddDirectory(ai)
AddDirectory(buildings)
AddDirectory(controls)
AddDirectory(desktops)
AddDirectory(drivers)
AddDirectory(factories)
AddDirectory(figures)
AddDirectory(gameData)
AddDirectory(gameTypes)
AddDirectory(helpers)
AddDirectory(ingameWindows)
AddDirectory(nodeObjs)
AddDirectory(ogl)
################################################################################

GETTEXT_CREATE_TRANSLATIONS(../RTTR/languages/rttr.pot ALL
							../RTTR/languages/rttr-de.po
							../RTTR/languages/rttr-es.po
							../RTTR/languages/rttr-sv.po
							../RTTR/languages/rttr-fi.po
							../RTTR/languages/rttr-fr.po
							../RTTR/languages/rttr-ru.po
							../RTTR/languages/rttr-nl.po
							../RTTR/languages/rttr-et.po
							../RTTR/languages/rttr-en_GB.po
							../RTTR/languages/rttr-sk.po
							../RTTR/languages/rttr-nds.po
							../RTTR/languages/rttr-tr.po
							../RTTR/languages/rttr-pl.po
							../RTTR/languages/rttr-pt.po
							../RTTR/languages/rttr-he.po
							../RTTR/languages/rttr-cs.po
							../RTTR/languages/rttr-hu.po
							../RTTR/languages/rttr-it.po
							../RTTR/languages/rttr-sl.po
							../RTTR/languages/rttr-nb.po
						   )

################################################################################

# bzip linkerbug-fix
SET(SOURCES_BZIP "")
IF ( "${COMPILEFOR}" STREQUAL "windows" )
	IF( IS_DIRECTORY "${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3" )
		SET(SOURCES_BZIP
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/blocksort.c
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/huffman.c
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/crctable.c
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/randtable.c
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/compress.c
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/decompress.c
			${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3/bzlib.c
		)
	ENDIF( IS_DIRECTORY "${CMAKE_SOURCE_DIR}/contrib/bzip2-1.0.3" )
ENDIF ( "${COMPILEFOR}" STREQUAL "windows" )

INCLUDE(AddFileDependencies)
ADD_FILE_DEPENDENCIES(${PROJECT_SOURCE_DIR}/build_version.cpp ${CMAKE_BINARY_DIR}/build_version.h)

SET(s25client_SRCS
	${PROJECT_SOURCE_DIR}/build_version.cpp
	${SOURCES_OTHER}
	${SOURCES_SUBDIRS}
)

IF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
	ADD_DEFINITIONS("-DAFX_TARG_DEU")

	IF ( "${COMPILEARCH}" STREQUAL "i386" )
		FIND_PROGRAM(WINDRES NAMES windres i686-pc-mingw32-windres i686-mingw32-windres i586-mingw32msvc-windres DOC "path to mingw's windres executable")
	ELSE ( "${COMPILEARCH}" STREQUAL "i386" )
		FIND_PROGRAM(WINDRES NAMES windres x86_64-pc-mingw32-windres x86_64-mingw32-windres amd64-mingw32msvc-windres DOC "path to mingw's windres executable")
	ENDIF ( "${COMPILEARCH}" STREQUAL "i386" )

	# Add Icon to Application
	ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/s25client.res.o
					   COMMAND ${WINDRES} -I${CMAKE_CURRENT_SOURCE_DIR}/../win32/ -i${CMAKE_CURRENT_SOURCE_DIR}/../win32/s25client.rc -o ${CMAKE_CURRENT_BINARY_DIR}/s25client.res.o)

	SET(s25client_SRCS ${s25client_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/s25client.res.o)

	ADD_FLAGS(CMAKE_EXE_LINKER_FLAGS -Wl,--stack,8388608)
ENDIF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")

IF ( "${COMPILEFOR}" STREQUAL "apple")
	CORRECT_LIB(OPENGL_gl_LIBRARY OpenGL)
	CORRECT_LIB(SDL_LIBRARY SDL)

	# Add the SDL-include flags to an apple build
	ADD_FLAGS(CMAKE_C_FLAGS -I${SDL_INCLUDE_DIR})
	ADD_FLAGS(CMAKE_CXX_FLAGS -I${SDL_INCLUDE_DIR})

	# Add library
	ADD_FLAGS(CMAKE_EXE_LINKER_FLAGS -framework OpenGL -L${CMAKE_SOURCE_DIR}/macos -lSDLmain)
ENDIF ( "${COMPILEFOR}" STREQUAL "apple")

################################################################################
# LUA
################################################################################

SET(LUA_VERSION "52")

IF ( "${COMPILEFOR}" STREQUAL "windows")
	IF ( "${COMPILEARCH}" STREQUAL "i386" )
		SET(LUA_DIR "${CMAKE_SOURCE_DIR}/contrib/lua/win32")
	ELSE ( "${COMPILEARCH}" STREQUAL "i386" )
		SET(LUA_DIR "${CMAKE_SOURCE_DIR}/contrib/lua/win64")
	ENDIF ( "${COMPILEARCH}" STREQUAL "i386" )
ENDIF ( "${COMPILEFOR}" STREQUAL "windows")

IF ( "${COMPILEFOR}" STREQUAL "linux")
	IF ( "${COMPILEARCH}" STREQUAL "i386" )
		SET(LUA_DIR "${CMAKE_SOURCE_DIR}/contrib/lua/lin32")
	ELSE ( "${COMPILEARCH}" STREQUAL "i386" )
		SET(LUA_DIR "${CMAKE_SOURCE_DIR}/contrib/lua/lin64")
	ENDIF ( "${COMPILEARCH}" STREQUAL "i386" )
ENDIF ( "${COMPILEFOR}" STREQUAL "linux")

IF ( "${COMPILEFOR}" STREQUAL "apple")
	SET(LUA_DIR "${CMAKE_SOURCE_DIR}/contrib/lua/mac")
ENDIF ( "${COMPILEFOR}" STREQUAL "apple")

IF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
	SET(LUA_LIB "${CMAKE_SOURCE_DIR}/contrib/lib/lua${LUA_VERSION}.lib")
ELSE ()
	SET(LUA_LIB "${LUA_DIR}/liblua${LUA_VERSION}.a")
ENDIF ()

MESSAGE(STATUS "Checking LUA library at ${LUA_LIB}")
IF ( NOT EXISTS "${LUA_LIB}" )
	SET(LUA_LIB "/usr/lib/liblua5.2.a")
	INCLUDE_DIRECTORIES("/usr/include/lua5.2")
ENDIF ( NOT EXISTS "${LUA_LIB}" )

IF ( NOT EXISTS "${LUA_LIB}" )
	SET(LUA_LIB "/usr/lib/liblua.so")
	INCLUDE_DIRECTORIES("/usr/include/")
ENDIF ( NOT EXISTS "${LUA_LIB}" )

MESSAGE(STATUS "Using LUA library from ${LUA_LIB}")

INCLUDE_DIRECTORIES("${LUA_DIR}/include")

################################################################################

IF (MSVC)
	SET(s25client_RC "${CMAKE_CURRENT_SOURCE_DIR}/../win32/s25client.rc")
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
	# disable warning 4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
	ADD_DEFINITIONS(/wd"4267")
	ADD_DEFINITIONS(/WX) # warning = error
	ADD_DEFINITIONS(/MP) # parallel compilation
ELSE()
	SET(s25client_RC "")
ENDIF()

ADD_EXECUTABLE(s25client ${s25client_SRCS} ${s25client_RC})
ADD_DEPENDENCIES(s25client updateversion)
TARGET_LINK_LIBRARIES(s25client
	siedler2
	lobby_c
	s25util
	mygettext
	${BZIP2_LIBRARIES}
	${OPENGL_gl_LIBRARY}
	${LUA_LIB}
)

IF ( "${COMPILEFOR}" STREQUAL "apple")
	TARGET_LINK_LIBRARIES(s25client ${SDL_LIBRARY} SDLmain)
	SET_TARGET_PROPERTIES(s25client PROPERTIES LINK_FLAGS "-framework Cocoa")
ENDIF ( "${COMPILEFOR}" STREQUAL "apple")

IF ( "${COMPILEFOR}" STREQUAL "windows")
	TARGET_LINK_LIBRARIES(s25client ole32 ws2_32 shlwapi imagehlp)
	IF (NOT MSVC)
		TARGET_LINK_LIBRARIES(s25client bfd iberty)
	ENDIF()
ENDIF ( "${COMPILEFOR}" STREQUAL "windows")

IF ( "${COMPILEFOR}" STREQUAL "linux")
	TARGET_LINK_LIBRARIES(s25client dl pthread)
ENDIF ( "${COMPILEFOR}" STREQUAL "linux")

IF (MSVC)
	SET(CONTRIB_DLL_DIR "${CMAKE_SOURCE_DIR}/contrib/bin" CACHE PATH "Path to dll files from contrib package")
	IF (EXISTS "${CONTRIB_DLL_DIR}/libcurl.dll")
		ADD_CUSTOM_COMMAND(TARGET s25client POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONTRIB_DLL_DIR} $<TARGET_FILE_DIR:s25client>)
	ELSE()
		MESSAGE(WARNING "Folder with DLLs not found. You may not be able to execute directly from VS")
	ENDIF()
	ADD_CUSTOM_COMMAND(TARGET s25client POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/RTTR" "${CMAKE_CURRENT_BINARY_DIR}/../RTTR")
	CMAKE_POLICY(SET CMP0026 OLD) # Required for use of LOCATION_*
	INCLUDE(CreateLaunchers)
	CREATE_DEFAULT_TARGET_LAUNCHER(s25client WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/..")
ENDIF()

INSTALL(TARGETS s25client RUNTIME DESTINATION ${BINDIR})

################################################################################
