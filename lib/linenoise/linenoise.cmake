add_library(linenoise INTERFACE)

set(LINENOISE_MAX_LINE 80 CACHE STRING "Input max line size in bytes")

if (NOT DEFINED LINENOISE_DIR)
    set(LINENOISE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/linenoise")
endif()

target_sources(linenoise INTERFACE
    ${LINENOISE_DIR}/linenoise.c
)

target_include_directories(linenoise INTERFACE 
    ${LINENOISE_DIR}/include       
    ${LINENOISE_DIR}/include/linenoise
)

target_compile_definitions(linenoise INTERFACE
    LINENOISE_MAX_LINE=${LINENOISE_MAX_LINE}
    LINENOISE_ALLOW_EMPTY=false
    LINENOISE_MALLOC=LINENOISE_MALLOC_FREERTOS
)

message("linenoise library available at ${LINENOISE_DIR}")