cmake_minimum_required (VERSION 2.6)
project (Pipeline)

IF(WIN32)

add_definitions("-DLIBRARY_EXTENSION=.dll")
add_definitions("-DLIB_EXPORT=__declspec(dllexport)")

ELSEIF (APPLE)

add_definitions("-DLIBRARY_EXTENSION=\".dylib\"")

ELSE()

add_definitions("-DLIBRARY_EXTENSION=.so")

ENDIF()

IF(UNIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-DLIB_EXPORT=")

ENDIF()

add_executable(Pipeline main.cpp )

add_subdirectory(methods/double)
add_subdirectory(methods/quarter)
add_subdirectory(methods/square)
