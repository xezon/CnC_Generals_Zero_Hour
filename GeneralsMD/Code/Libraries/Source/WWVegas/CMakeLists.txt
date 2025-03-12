# Interface libraries to set common defines and includes, avoid duplication later
add_library(z_wwcommon INTERFACE)

target_compile_definitions(z_wwcommon INTERFACE
    #NOMINMAX
    WIN32_LEAN_AND_MEAN
    $<$<CONFIG:Debug>:WWDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

target_compile_options(z_wwcommon INTERFACE
    ${GENZH_FLAGS}
)

target_link_libraries(z_wwcommon INTERFACE
    stlport
    milesstub
    d3d8lib
)

target_include_directories(z_wwcommon INTERFACE
    WWDebug
    WWLib
    WWMath
    Wwutil
    WWSaveLoad
    WW3D2
    wwshade
    WWAudio
    .
)

add_subdirectory(WWDebug)
add_subdirectory(WWLib)
add_subdirectory(WWMath)
add_subdirectory(Wwutil)
add_subdirectory(WWSaveLoad)
add_subdirectory(WW3D2)
add_subdirectory(WWDownload)
add_subdirectory(wwshade)

# Helpful interface to bundle the ww modules together.
add_library(z_wwvegas INTERFACE)

target_include_directories(z_wwvegas INTERFACE
    WWDebug
    WWLib
    WWMath
    WW3D2
    WWDownload
    WWSaveLoad
    wwshade
    Wwutil
    .
)

target_link_libraries(z_wwvegas INTERFACE
    z_wwdebug
    z_wwlib
    z_wwmath
    z_wwutil
    z_wwsaveload
    z_ww3d2
    z_wwdownload
    z_wwshade
)
