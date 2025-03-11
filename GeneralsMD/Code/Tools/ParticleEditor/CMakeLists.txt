# Set source files
set(PARTICLEED_SRC
    CButtonShowColor.cpp
    CColorAlphaDialog.cpp
    CSwitchesDialog.cpp
    EmissionTypePanels.cpp
    MoreParmsDialog.cpp
    ParticleEditor.cpp
    ParticleEditorDialog.cpp
    ParticleTypePanels.cpp
    ShaderTypePanels.cpp
    StdAfx.cpp
    VelocityTypePanels.cpp
    CButtonShowColor.h
    CColorAlphaDialog.h
    CSwitchesDialog.h
    EmissionTypePanels.h
    ISwapablePanel.h
    MoreParmsDialog.h
    ParticleEditor.h
    ParticleEditorDialog.h
    ParticleEditorExport.h
    ParticleTypePanels.h
    Resource.h
    ShaderTypePanels.h
    StdAfx.h
    VelocityTypePanels.h
)

# Targets to build.
add_library(particleeditor SHARED)

set_target_properties(particleeditor PROPERTIES PREFIX "")

target_include_directories(particleeditor PRIVATE
    include
    res
)

target_link_libraries(particleeditor PRIVATE
    zi_gameengine_include
    zi_libraries_include
    zi_libraries_source_wwvegas
    zi_libraries_source_wwvegas_wwlib
    stlport
    winmm
    imm32
    vfw32
    d3d8lib
    profile
    dbghelplib
)

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    target_link_options(particleeditor PRIVATE /NODEFAULTLIB:libci.lib /NODEFAULTLIB:libc.lib)
    target_compile_definitions(particleeditor PRIVATE _AFXDLL)
    target_sources(particleeditor PRIVATE ParticleEditor.rc)
    set_target_properties(particleeditor PROPERTIES OUTPUT_NAME ParticleEditor)
else()
    set_target_properties(particleeditor PROPERTIES OUTPUT_NAME particleeditor)
endif()

target_sources(particleeditor PRIVATE ${PARTICLEED_SRC})
