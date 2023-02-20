set(EXECUTABLE_NAME psu)

# Configuration variables for all the components
set(enableConsoleTask ON)
set(enableLEDTask ON)
set(enableLEDCommand ON)


if(NOT enableConsoleTask)
     set(enableLEDCommand OFF)
     set(enableSensorCommand OFF)
endif()

add_executable(${EXECUTABLE_NAME} main.c)
add_subdirectory(components/tasks/led)
add_subdirectory(components/tasks/console)
add_subdirectory(components/tasks/cvolt)

# Link to built libraries
target_link_libraries(${EXECUTABLE_NAME} 
     # ----------------------------
     # -- application components --
     # ----------------------------
     console
     led
     cvolt
     # ---------------------------
     # -- Third party libraries --
     # ---------------------------
     C-Macro-Collections
     linenoise 
     argtable2
     # ----------------------------------
     # -- Raspberry Pi Pico SDK libraries
     # ----------------------------------
     hardware_pwm
     pico_stdlib
     # ------------------------
     # -- FreeRTOS libraries --
     # ------------------------
     MyFreeRTOS-Kernel 
     ${HEAP_MEMORY_MODEL}       
)

# Enables stdio on RP2040 UART and/or USB CDC profile
pico_enable_stdio_usb(${EXECUTABLE_NAME}  1)
pico_enable_stdio_uart(${EXECUTABLE_NAME} 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${EXECUTABLE_NAME})