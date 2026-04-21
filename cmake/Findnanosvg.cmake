# nanosvg
include(FetchContent)
FetchContent_Declare(
    nanosvg
    GIT_REPOSITORY https://github.com/memononen/nanosvg.git
    GIT_TAG master
)
FetchContent_MakeAvailable(nanosvg)

# Expose src/ for include paths when building from source tree
if (TARGET nanosvg)
    target_include_directories(nanosvg PUBLIC
        $<BUILD_INTERFACE:${nanosvg_SOURCE_DIR}/src>
    )
endif()
if (TARGET nanosvgrast)
    target_include_directories(nanosvgrast PUBLIC
        $<BUILD_INTERFACE:${nanosvg_SOURCE_DIR}/src>
    )
endif()
