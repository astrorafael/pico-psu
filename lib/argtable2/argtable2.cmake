
if (NOT DEFINED ARGTABLE2_DIR)
    set(ARGTABLE2_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/argtable2")
endif()


set( HAVE_GETOPT_H   OFF CACHE BOOL "Have the getopt library")
set( HAVE_INTTYPES_H ON CACHE BOOL "Have the file inttypes.h")
set( HAVE_MEMORY_H   ON CACHE BOOL "Have the file memory.h")
set( HAVE_STDLIB_H   ON CACHE BOOL "Have the file stdlib.h")
set( HAVE_STRINGS_H  ON CACHE BOOL "Have the strings.h")
set( HAVE_STRING_H   ON CACHE BOOL "Have the file string.h")
set( STDC_HEADERS    ON CACHE BOOL "Have std C header files")
set( ARGTABLE2_MALLOC 2 CACHE STRING "Heap memory allocator. 1=standard library, 2=FreeRTOS" )

set(ARGTABLE2_GETOPT_ALTERNATE_SOURCES "")
if( HAVE_GETOPT_H )
    list(APPEND HAVE_OPTIONS HAVE_GETOPT_H )
else()
    list(APPEND ARGTABLE2_GETOPT_ALTERNATE_SOURCES "${ARGTABLE2_DIR}/getopt.c")
    list(APPEND ARGTABLE2_GETOPT_ALTERNATE_SOURCES "${ARGTABLE2_DIR}/getopt1.c")
endif()
if( HAVE_INTTYPES_H )
    list(APPEND HAVE_OPTIONS  HAVE_INTTYPES_H )
endif()
if( HAVE_MEMORY_H )
    list(APPEND HAVE_OPTIONS  HAVE_MEMORY_H )
endif()
if( HAVE_STDLIB_H )
    list(APPEND HAVE_OPTIONS  HAVE_STDLIB_H )
endif()
if( HAVE_STRINGS_H )
    list(APPEND HAVE_OPTIONS  HAVE_STRINGS_H )
endif()
if( HAVE_STRING_H )
    list(APPEND HAVE_OPTIONS  HAVE_STRING_H )
endif()
if( STDC_HEADERS )
    list(APPEND HAVE_OPTIONS  STDC_HEADERS )
endif()


add_library(argtable2 INTERFACE)
target_sources(argtable2 INTERFACE
    ${ARGTABLE2_DIR}/arg_date.c
    ${ARGTABLE2_DIR}/arg_dbl.c
    ${ARGTABLE2_DIR}/arg_flt.c # Added by astrorafael
    ${ARGTABLE2_DIR}/arg_end.c
    ${ARGTABLE2_DIR}/arg_file.c
    ${ARGTABLE2_DIR}/arg_int.c
    ${ARGTABLE2_DIR}/arg_lit.c
    ${ARGTABLE2_DIR}/arg_rem.c
    ${ARGTABLE2_DIR}/arg_rex.c
    ${ARGTABLE2_DIR}/arg_str.c
    ${ARGTABLE2_DIR}/argtable2.c
    ${ARGTABLE2_GETOPT_ALTERNATE_SOURCES}
)

target_include_directories(argtable2 INTERFACE 
    ${ARGTABLE2_DIR}/include           # This is used internally
    ${ARGTABLE2_DIR}/include/argtable2 # Prefer this for external programs
)

target_compile_definitions(argtable2 INTERFACE
    ARGTABLE2_MALLOC=${ARGTABLE2_MALLOC}
    ${HAVE_OPTIONS}
)

message("argtable2 library available at ${ARGTABLE2_DIR}")