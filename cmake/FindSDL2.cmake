# =============================================================================
# Custom FindSDL2 module for cross-platform support.
# Locates SDL2 headers and libraries and sets up a standard CMake target.
# =============================================================================

# Common installation locations across platforms
set(SDL2_SEARCH_PATHS
    /usr/local
    /usr
    /opt/local
    /opt
    "C:/Program Files/SDL2"
    "C:/Program Files (x86)/SDL2"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2"
)

# 1. Look for the header directory containing SDL.h
find_path(SDL2_INCLUDE_DIR
    NAMES SDL.h
    PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_SEARCH_PATHS}
)

# 2. Look for the main SDL2 compiled library binary
find_library(SDL2_LIBRARY
    NAMES SDL2 sdl2
    PATH_SUFFIXES lib lib/x64 lib/x86
    PATHS ${SDL2_SEARCH_PATHS}
)

# 3. Handle Windows specific WinMain entry point requirement
if(WIN32)
    find_library(SDL2MAIN_LIBRARY
        NAMES SDL2main sdl2main
        PATH_SUFFIXES lib lib/x64 lib/x86
        PATHS ${SDL2_SEARCH_PATHS}
    )
endif()

# 4. Verify both headers and main libraries were found successfully
include(FindPackageHandleStandardArgs)
if(WIN32)
    find_package_handle_standard_args(SDL2
        REQUIRED_VARS SDL2_LIBRARY SDL2MAIN_LIBRARY SDL2_INCLUDE_DIR
    )
else()
    find_package_handle_standard_args(SDL2
        REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR
    )
endif()

# 5. Create a modern, unified CMake target if everything was found
if(SDL2_FOUND AND NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
        IMPORTED_LOCATION "${SDL2_LIBRARY}"
    )
    
    # On Windows, link the WinMain library alongside the core library
    if(WIN32 AND SDL2MAIN_LIBRARY)
        set_property(TARGET SDL2::SDL2 APPEND PROPERTY
            INTERFACE_LINK_LIBRARIES "${SDL2MAIN_LIBRARY}"
        )
    endif()
endif()

# Hide tracking variables from the standard GUI configuration screen
mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY SDL2MAIN_LIBRARY)
