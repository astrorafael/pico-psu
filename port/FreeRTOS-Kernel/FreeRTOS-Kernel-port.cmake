# Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

# Called after the Raspberry Pi Pico SDK has been initialized to add our libraries


if (NOT DEFINED FREERTOS_CUSTOM_CONFIG_DIR)
    set(FREERTOS_CUSTOM_CONFIG_DIR "${CMAKE_CURRENT_LIST_DIR}/port/FreeRTOS-Kernel")
endif()

set(FREERTOS_RP2040_PATH ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040)

message(STATUS "CMake build flag is ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FREERTOS_CONFIG_FILE_INCLUDE_PATH  ${FREERTOS_CUSTOM_CONFIG_DIR}/include/debug)
else()
    set(FREERTOS_CONFIG_FILE_INCLUDE_PATH  ${FREERTOS_CUSTOM_CONFIG_DIR}/include/release)
endif()

# ================================= #
# The very core library of FreeRTOS #
# ================================= #

add_library(MyFreeRTOS-Kernel-Core INTERFACE)
target_sources(MyFreeRTOS-Kernel-Core INTERFACE
        ${FREERTOS_KERNEL_PATH}/event_groups.c
        ${FREERTOS_KERNEL_PATH}/list.c
        ${FREERTOS_KERNEL_PATH}/queue.c
        ${FREERTOS_KERNEL_PATH}/stream_buffer.c
        ${FREERTOS_KERNEL_PATH}/tasks.c
        ${FREERTOS_KERNEL_PATH}/timers.c
        # This is for application-defined static allocations
        ${CMAKE_CURRENT_LIST_DIR}/static.c

)

target_include_directories(MyFreeRTOS-Kernel-Core INTERFACE 
        ${FREERTOS_KERNEL_PATH}/include 
        ${FREERTOS_CUSTOM_CONFIG_DIR}/include       # additional heap extension files.h file
        ${FREERTOS_CONFIG_FILE_INCLUDE_PATH} # For FreeRTOSConfig.h file
)


if (PICO_SDK_VERSION_STRING VERSION_GREATER_EQUAL "1.3.2")
    target_compile_definitions(MyFreeRTOS-Kernel-Core INTERFACE
            PICO_CONFIG_RTOS_ADAPTER_HEADER=${FREERTOS_RP2040_PATH}/include/freertos_sdk_config.h
    )
endif()

# ===================================== #
# FreeRTOS core + specific port library #
# ===================================== #

add_library(MyFreeRTOS-Kernel INTERFACE)
target_sources(MyFreeRTOS-Kernel INTERFACE ${FREERTOS_RP2040_PATH}/port.c)
 
target_include_directories(MyFreeRTOS-Kernel INTERFACE
        ${FREERTOS_RP2040_PATH}/include
        ${FREERTOS_CUSTOM_CONFIG_DIR}
)

target_link_libraries(MyFreeRTOS-Kernel INTERFACE
        MyFreeRTOS-Kernel-Core
        pico_base_headers
        hardware_exception
)

target_compile_definitions(MyFreeRTOS-Kernel INTERFACE
        LIB_FREERTOS_KERNEL=1
        FREERTOS_KERNEL_SMP=0
)

# ===================================== #
# Task Static memory management library #
# ===================================== #

add_library(MyFreeRTOS-Kernel-Static INTERFACE)
target_compile_definitions(MyFreeRTOS-Kernel-Static INTERFACE
        configSUPPORT_STATIC_ALLOCATION=1
)

target_sources(MyFreeRTOS-Kernel-Static INTERFACE ${FREERTOS_RP2040_PATH}/idle_task_static_memory.c)
target_link_libraries(MyFreeRTOS-Kernel-Static INTERFACE MyFreeRTOS-Kernel)

# =================================== #
# Dynamic memory management libraries #
# =================================== #

# The various Memory management libraries are declared here
# We will choose for each target
add_library(MyFreeRTOS-Kernel-Heap1 INTERFACE)
target_sources(MyFreeRTOS-Kernel-Heap1 INTERFACE ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_1.c)
target_link_libraries(MyFreeRTOS-Kernel-Heap1 INTERFACE MyFreeRTOS-Kernel)

add_library(MyFreeRTOS-Kernel-Heap2 INTERFACE)
target_sources(MyFreeRTOS-Kernel-Heap2 INTERFACE ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_2.c)
target_link_libraries(MyFreeRTOS-Kernel-Heap2 INTERFACE MyFreeRTOS-Kernel)

add_library(MyFreeRTOS-Kernel-Heap3 INTERFACE)
target_sources(MyFreeRTOS-Kernel-Heap3 INTERFACE 
        ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_3.c
        ${FREERTOS_CUSTOM_CONFIG_DIR}/heap_ext_3.c
)
target_include_directories(MyFreeRTOS-Kernel-Heap3 INTERFACE
     ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(MyFreeRTOS-Kernel-Heap3 INTERFACE MyFreeRTOS-Kernel)

add_library(MyFreeRTOS-Kernel-Heap4 INTERFACE)
target_sources(MyFreeRTOS-Kernel-Heap4 INTERFACE 
        ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
        ${FREERTOS_CUSTOM_CONFIG_DIR}/heap_ext_4.c
)
target_include_directories(MyFreeRTOS-Kernel-Heap4 INTERFACE
     ${FREERTOS_CUSTOM_CONFIG_DIR}/include
)
target_link_libraries(MyFreeRTOS-Kernel-Heap4 INTERFACE MyFreeRTOS-Kernel)

add_library(MyFreeRTOS-Kernel-Heap5 INTERFACE)
target_sources(MyFreeRTOS-Kernel-Heap5 INTERFACE ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_5.c)
target_link_libraries(MyFreeRTOS-Kernel-Heap5 INTERFACE MyFreeRTOS-Kernel)

message("FreeRTOS-Kernel config available at ${FREERTOS_CUSTOM_CONFIG_DIR}")