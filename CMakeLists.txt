cmake_minimum_required (VERSION 2.6)
project (Pipeline)

IF(WIN32)

add_definitions("-DLIBRARY_EXTENSION=\".dll\"")
add_definitions("-DLIB_EXPORT=__declspec(dllexport)")

ELSEIF (APPLE)

add_definitions("-DLIBRARY_EXTENSION=\".dylib\"")

ELSE()

add_definitions("-DLIBRARY_EXTENSION=\".so\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")

ENDIF()

IF(UNIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-DLIB_EXPORT=")

ENDIF()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/..)

add_executable(Pipeline main.cpp )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../libs)

add_subdirectory(methods/double)
add_subdirectory(methods/quarter)
add_subdirectory(methods/square)
