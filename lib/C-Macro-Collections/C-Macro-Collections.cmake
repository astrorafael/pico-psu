add_library(C-Macro-Collections INTERFACE)


if (NOT DEFINED C_MACRO_COLLECTIONS_DIR)
    set(C_MACRO_COLLECTIONS_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/C-Macro-Collections")
endif()


target_sources(C-Macro-Collections INTERFACE
 
)

target_include_directories(C-Macro-Collections INTERFACE 
    ${C_MACRO_COLLECTIONS_DIR}/include       # For header.h files
    ${C_MACRO_COLLECTIONS_DIR}/include/cmc
)

target_compile_definitions(C-Macro-Collections INTERFACE
    UINT64_C=uint64_t   # Fix compiler warning.
)

message("C-Macro-Collections library available at ${C_MACRO_COLLECTIONS_DIR}")