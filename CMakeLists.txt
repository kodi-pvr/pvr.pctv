cmake_minimum_required(VERSION 3.5)
project(pvr.pctv)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(p8-platform REQUIRED)
find_package(JsonCpp REQUIRED)

include_directories(${kodiplatform_INCLUDE_DIRS}
                    ${p8-platform_INCLUDE_DIRS}
                    ${JSONCPP_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

set(DEPLIBS ${p8-platform_LIBRARIES}
            ${JSONCPP_LIBRARIES})

set(PCTV_SOURCES src/client.cpp
                 src/md5.cpp
                 src/PctvData.cpp
                 src/rest.cpp)

set(PCTV_HEADERS src/client.h
                 src/md5.h
                 src/PctvData.h
                 src/rest.h)

build_addon(pvr.pctv PCTV DEPLIBS)

include(CPack)
