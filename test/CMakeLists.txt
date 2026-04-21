set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

find_package(pntr REQUIRED)
find_package(nanosvg REQUIRED)

add_executable(pntr_nanosvg_test pntr_nanosvg_test.c)
target_link_libraries(pntr_nanosvg_test PUBLIC
    pntr
    nanosvg
    nanosvgrast
    pntr_nanosvg
)
set_property(TARGET pntr_nanosvg_test PROPERTY C_STANDARD 11)

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_test(NAME pntr_nanosvg_test COMMAND pntr_nanosvg_test)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
