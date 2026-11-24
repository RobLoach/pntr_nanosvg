cmake_minimum_required(VERSION 3.11)
project(pntr_nanosvg
    DESCRIPTION "pntr_nanosvg"
    HOMEPAGE_URL "https://github.com/robloach/pntr_nanosvg"
    VERSION 0.1.0
    LANGUAGES C
)

# pntr_nanosvg
add_library(pntr_nanosvg INTERFACE)
target_include_directories(pntr_nanosvg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
if (UNIX)
    # nanosvg's implementation needs libm
    target_link_libraries(pntr_nanosvg INTERFACE m)
endif()

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(PNTR_NANOSVG_IS_MAIN TRUE)
else()
    set(PNTR_NANOSVG_IS_MAIN FALSE)
endif()

option(PNTR_NANOSVG_BUILD_TESTS "pntr_nanosvg: Tests" ${PNTR_NANOSVG_IS_MAIN})

# Testing
if (PNTR_NANOSVG_BUILD_TESTS)
    include(CTest)
    enable_testing()
    if (BUILD_TESTING)
        set(CTEST_CUSTOM_TESTS_IGNORE
            pkg-config--static
        )
        list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
        add_subdirectory(test)
    endif()
endif()
