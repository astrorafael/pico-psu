add_library(led INTERFACE)



if(enableLEDTask)
     set(INCLUDE_LED_TASK 1)
     message(STATUS "Including LED component")
else()
    set(INCLUDE_LED_TASK 0)
    message(STATUS "Excluding LED component")
endif()

if(enableLEDCommand)
     set(INCLUDE_LED_CMD 1)
     message(STATUS "LED component IS managed by commands")
else()
    set(INCLUDE_LED_CMD 0)
     message(STATUS "LED component NOT managed by commands")
endif()


target_sources(led INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/task.c
    ${CMAKE_CURRENT_LIST_DIR}/src/command.c
)

target_include_directories(led INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_definitions(led INTERFACE
    INCLUDE_LED_TASK=${INCLUDE_LED_TASK}
    INCLUDE_LED_CMD=${INCLUDE_LED_CMD}
)

