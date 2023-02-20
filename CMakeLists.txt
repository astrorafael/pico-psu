# =================
# PROJECT CMakeList
# =================

# ------------
# Global stuff
# ------------

cmake_minimum_required(VERSION 3.14)

# Project data
set(PROJECT_NAME "pico-psu")
set(BUILD_NUMBER "0")

# Languages standard
set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

# Some more configuration variables
set(PICO_SDK_PATH        $ENV{HOME}/repos/ext/pico/pico-sdk            CACHE PATH "Directory where the Raspberry Pi Pico SDK resides")
set(FREERTOS_KERNEL_PATH $ENV{HOME}/repos/ext/FreeRTOS/FreeRTOS-Kernel CACHE PATH "Directory where the FreeRTOS kernel resides")
set(HEAP_MEMORY_MODEL   MyFreeRTOS-Kernel-Heap3 CACHE STRING "Selected heap memory model (from 1 to 5)")
set(PICO_BOARD pico)   # This must not be a CACHE variable, otherwise the SDK don't get it!

# Pull in Pico SDK (must be before project)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Pull in FreeRTOS (must be before project)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Name the project
project(pico-psu
        LANGUAGES C CXX ASM
        DESCRIPTION "Constant Current LED Power Supply Unit for TESS-W calibration"
)

set(LINENOISE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/linenoise" CACHE STRING "Linenoise lib to read a line")
include("${LINENOISE_DIR}/linenoise.cmake")

set(ARGTABLE2_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/argtable2" CACHE STRING "argtable lib to parse command line")
include("${ARGTABLE2_DIR}/argtable2.cmake")

set(C_MACRO_COLLECTIONS_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/C-Macro-Collections" CACHE STRING "C Macro Collections library")
include("${C_MACRO_COLLECTIONS_DIR}/C-Macro-Collections.cmake")

SET(FREERTOS_CUSTOM_CONFIG_DIR "${CMAKE_CURRENT_LIST_DIR}/port/FreeRTOS-Kernel" CACHE STRING "Local FreeRTOS Config")
include("${FREERTOS_CUSTOM_CONFIG_DIR}/FreeRTOS-Kernel-port.cmake")

# ----------------------
# Start the ball rolling
# ----------------------

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
)

add_subdirectory(src)