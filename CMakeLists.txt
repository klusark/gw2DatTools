cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(gw2DatTools)

include_directories(include)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAG}")

add_library(gw2DatTools

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
