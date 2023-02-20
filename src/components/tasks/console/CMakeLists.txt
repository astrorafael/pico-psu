add_library(console INTERFACE)

if(enableConsoleTask)
     set(INCLUDE_CONSOLE_TASK 1)
     message(STATUS "Including Console component")
else()
    set(INCLUDE_CONSOLE_TASK 0)
    message(STATUS "Excluding Console component")
endif()

 set(CONSOLE_PROMPT "\"psu> \"")

target_sources(console INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/task.c
)

target_include_directories(console INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_definitions(console INTERFACE
  INCLUDE_CONSOLE_TASK=${INCLUDE_CONSOLE_TASK}
  CONSOLE_PROMPT=${CONSOLE_PROMPT}
)

