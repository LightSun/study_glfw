cmake_minimum_required(VERSION 3.4.1)
project(studyGlew)

#gles
#如果当前系统版本过低设置拒绝编译
if (${ANDROID_PLATFORM_LEVEL} LESS 11)
    message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 (currently using ${ANDROID_PLATFORM_LEVEL}).")
    return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
    add_definitions("-DDYNAMIC_ES3")
    set(OPENGL_LIB GLESv2)
else ()
    set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 11)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/src/main/lib/${ANDROID_ABI})
include_directories(src/main/cpp/include)

add_library(bx STATIC IMPORTED)
set_target_properties(bx PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libbxDebug.a)

#halfbuzz + freetype + icu
set(HARFBUZZ_BUILD_ICU ON CACHE BOOL "Enable building of ICU")
set(HARFBUZZ_BUILD_UCDN ON CACHE BOOL "Enable building of UCDN")

set(DIR_HALFBUZZ_FREETYPE src/main/cpp/harfbuzz-icu-freetype)
include_directories(${DIR_HALFBUZZ_FREETYPE}/freetype/include)
include_directories(${DIR_HALFBUZZ_FREETYPE}/harfbuzz/src)

add_subdirectory(${DIR_HALFBUZZ_FREETYPE} harfbuzz_out)

# glew need X11 , android doesn't have
#include_directories(src/main/cpp/glew/include)
#aux_source_directory(src/main/cpp/glew/src src_glew)

aux_source_directory(src/main/cpp src_all)
add_library(studyGlfw
    SHARED
    ${src_all}
)
set_target_properties(studyGlfw PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(studyGlfw
    ${OPENGL_LIB}
    bx
    harfbuzz
    freetype
    icucommon
    log
)
