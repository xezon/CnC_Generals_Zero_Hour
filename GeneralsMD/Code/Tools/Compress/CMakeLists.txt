set(COMRPESS_SRC
    "Compress.cpp"
    "../CRCDiff/debug.cpp"
    "../CRCDiff/debug.h"
)

add_executable(compress WIN32)

target_link_libraries(compress PRIVATE
    zi_libraries_include
    zi_libraries_source
    compression
)

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    if(MSVC_VERSION LESS 1300) # VS6
        target_compile_definitions(compress PRIVATE vsnprintf=_vsnprintf)
    endif()
    target_link_options(compress PRIVATE /subsystem:console)
endif()

target_sources(compress PRIVATE ${COMRPESS_SRC})
