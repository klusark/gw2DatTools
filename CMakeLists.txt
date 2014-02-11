cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(gw2DatTools)

include_directories(include)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAG}")


set(SOURCES
src/gw2DatTools/c_api/compression_inflateDatFileBuffer.cpp
src/gw2DatTools/compression/huffmanTreeUtils.cpp
src/gw2DatTools/compression/inflateDatFileBuffer.cpp
src/gw2DatTools/compression/inflateTextureFileBuffer.cpp
src/gw2DatTools/exception/Exception.cpp
src/gw2DatTools/format/ANDat.cpp
src/gw2DatTools/format/Mapping.cpp
src/gw2DatTools/format/Mft.cpp
src/gw2DatTools/interface/ANDatInterface.cpp
)

set(HEADERS
include/gw2DatTools/c_api/compression_inflateDatFileBuffer.h
include/gw2DatTools/compression/inflateDatFileBuffer.h
include/gw2DatTools/compression/inflateTextureFileBuffer.h
include/gw2DatTools/exception/Exception.h
include/gw2DatTools/interface/ANDatInterface.h
)

add_library(gw2DatTools SHARED ${SOURCES} ${HEADERS})

install(TARGETS gw2DatTools DESTINATION "lib")
install(DIRECTORY include/gw2DatTools DESTINATION "include")
