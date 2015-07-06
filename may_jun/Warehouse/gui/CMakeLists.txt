PROJECT(MC)

cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

INCLUDE (CheckIncludeFiles)

# --------------------------------------------------------------------------
# Build options

option(BUILD_SHARED "Build Shared Libraries" OFF)
SET(FOX_LIBNAME "FOX-1.6" CACHE STRING "FOX Toolkit library name")

ADD_DEFINITIONS(-DHAVE_JPEG_H=1)
ADD_DEFINITIONS(-DHAVE_PNG_H=1)
ADD_DEFINITIONS(-DHAVE_TIFF_H=1)
ADD_DEFINITIONS(-DHAVE_ZLIB_H=1)
ADD_DEFINITIONS(-DHAVE_OPENGL)

# --------------------------------------------------------------------------
# External Libraries

find_path(FOX_INCLUDE_DIR
   NAMES FXApp.h
   PATH  /usr/local/include/fox-1.6
)
find_path(FOX_LINK_DIR
   NAMES libFOX-1.6.a
   PATH  /usr/local/lib
)


############################################################################
#find_path(MY_OWN_HEAD_DIR
#  PATH /home/yuting/Desktop/myTest/g2
#)
############################################################################


# --------------------------------------------------------------------------
# Include dirs
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${FOX_INCLUDE_DIR}
  ${MY_OWN_HEAD_DIR}
)

# --------------------------------------------------------------------------
# Link directory
link_directories (
  ${CMAKE_CURRENT_BINARY_DIR}
  ${FOX_LINK_DIR}
)

# generate position independent code to link newmat static library
# to shared object
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


# --------------------------------------------------------------------------
# Build
add_library(MClib MConnectorWindow.cpp)

add_executable(MC interface.cpp)
target_link_libraries(MC
  ${FOX_LIBNAME}
  ${MY_OWN_HEAD_DIR}
  pthread
  m
  MClib
  )

