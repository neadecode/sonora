cmake_minimum_required(VERSION 3.16)

project(backend LANGUAGES C)

#variable for adding
set(HEADERS
    include/sonora/device_macros.h
    include/sonora/error.h
    include/sonora/sonora.h
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_IMPL
        src/win/sonora_win.c
        src/win/win_utils.h
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_IMPL
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM_IMPL
    )
endif()

#esto buildea la libreria
add_library(sonora SHARED
    ${PLATFORM_IMPL}
    ${HEADERS}
)

#esto es para el linker 
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(sonora PRIVATE winmm)
endif()
target_include_directories(sonora PUBLIC include)
target_compile_options(sonora PRIVATE -w)