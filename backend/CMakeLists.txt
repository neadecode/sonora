cmake_minimum_required(VERSION 3.16)

project(backend LANGUAGES C)

#variable for adding
set(HEADERS
    include/sonora/internal.h
    include/sonora/macro.h
    include/sonora/sonora.h
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_IMPL
        src/win/winmm.c
        src/win/winmm.h
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
    sonora_public.c
    ${PLATFORM_IMPL}
    ${HEADERS}
)

target_include_directories(sonora PUBLIC include)
#LINKER
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(sonora PRIVATE winmm)
endif()
#COMPILER FLAGS
target_compile_options(sonora PRIVATE -w)