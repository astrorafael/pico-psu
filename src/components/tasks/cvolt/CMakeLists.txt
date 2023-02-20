add_library(cvolt INTERFACE)

target_sources(cvolt INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/task.c
    ${CMAKE_CURRENT_LIST_DIR}/src/commands.c
    ${CMAKE_CURRENT_LIST_DIR}/src/commands/volt.c
    ${CMAKE_CURRENT_LIST_DIR}/src/commands/linstep.c
    ${CMAKE_CURRENT_LIST_DIR}/src/commands/next.c
)

target_include_directories(cvolt INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

#target_compile_definitions(cvolt INTERFACE)

