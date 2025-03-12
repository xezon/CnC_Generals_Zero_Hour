set(MAPCACHEBUILDER_SRC
    "Include/WinMain.h"
    "Resource/Resource.h"
    "Source/WinMain.cpp"
)

add_executable(z_mapcachebuilder WIN32)
set_target_properties(z_mapcachebuilder PROPERTIES OUTPUT_NAME mapcachebuilder)

target_include_directories(z_mapcachebuilder PRIVATE
    Include
    Resource
)
#
target_link_libraries(z_mapcachebuilder PRIVATE
    zi_libraries_include
    winmm
    imm32
    vfw32
    z_profile
    dbghelplib
    z_gameengine
    z_gameenginedevice
)

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    target_sources(z_mapcachebuilder PRIVATE Resource/MapCacheBuilder.rc)
endif()

target_sources(z_mapcachebuilder PRIVATE ${MAPCACHEBUILDER_SRC})
