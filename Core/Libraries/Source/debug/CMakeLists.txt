set(DEBUG_SRC
    "debug/debug_cmd.cpp"
    "debug/debug_cmd.h"
    "debug/debug_debug.cpp"
    "debug/debug_debug.h"
    "debug/debug_doc.h"
    "debug/debug_except.cpp"
    "debug/debug_getdefaultcommands.cpp"
    "debug/debug_internal.cpp"
    "debug/debug_io_con.cpp"
    "debug/debug_io_flat.cpp"
    "debug/debug_io_net.cpp"
    "debug/debug_io_ods.cpp"
    "debug/debug_io.h"
    "debug/debug_macro.h"
    "debug/debug_stack.cpp"
    "debug/debug_stack.h"
    "debug/debug.h"
    "debug/internal_except.h"
    "debug/internal_io.h"
    "debug/internal.h"
)

add_library(core_debug STATIC)

target_sources(core_debug PRIVATE ${DEBUG_SRC})

target_include_directories(core_debug INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_precompile_headers(core_debug PRIVATE
    [["Precompiled/precompiled.h"]] # Must be first
    "debug/debug.h"
    "debug/internal.h"
    "debug/internal_except.h"
    "debug/internal_io.h"
    <windows.h>
)

target_link_libraries(core_debug PRIVATE
    depsi_always # Gives force included headers. Link early.
    core_config
    deps_utility
    stlport
)
