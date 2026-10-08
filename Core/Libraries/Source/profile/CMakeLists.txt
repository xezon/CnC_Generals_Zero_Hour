set(PROFILE_SRC
    "profile/internal_cmd.h"
    "profile/internal_funclevel.h"
    "profile/internal_highlevel.h"
    "profile/internal_result.h"
    "profile/internal.h"
    "profile/profile_cmd.cpp"
    "profile/profile_doc.h"
    "profile/profile_funclevel.cpp"
    "profile/profile_funclevel.h"
    "profile/profile_highlevel.cpp"
    "profile/profile_highlevel.h"
    "profile/profile_result.cpp"
    "profile/profile_result.h"
    "profile/profile.cpp"
    "profile/profile.h"
)

add_library(core_profile_legacy STATIC)

target_sources(core_profile_legacy PRIVATE ${PROFILE_SRC})

target_include_directories(core_profile_legacy INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_precompile_headers(core_profile_legacy PRIVATE
    [["Precompiled/precompiled.h"]] # Must be first
    "profile/profile.h"
    "profile/internal.h"
    <windows.h>
)

target_link_libraries(core_profile_legacy PRIVATE
    depsi_always # Gives force included headers. Link early.
    core_config
    core_debug
    deps_utility
    stlport
)
