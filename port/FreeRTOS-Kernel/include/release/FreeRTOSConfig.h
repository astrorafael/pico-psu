// STEP BY STEP DEBUGGIN
/*
 * FreeRTOS V202107.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* ***************** */
/* Scheduler Related */
/* ***************** */
#define configUSE_PREEMPTION 1    // By a higher priority task. If 0, cooperative scheduler with taskYIELD()
#define configUSE_TICKLESS_IDLE 0 // Set to 1 to use the low power tickless mode,
#define configUSE_IDLE_HOOK 0     // Extend Idle Task functionality with vApplicationIdleHook()
#define configUSE_TICK_HOOK 0
#define configCPU_CLOCK_HZ 125000000                           // RP2040 system clock
#define configTICK_RATE_HZ ((TickType_t)100)                   // The RTOS demo apps use 1000Hz, higher than would normally be required.
#define configMAX_PRIORITIES 8                                 // The less, the better
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0              // If set, #priorities no greater than 32. See section 3.5.
#define configMINIMAL_STACK_SIZE ((configSTACK_DEPTH_TYPE)128) // For the Idle Task only. In words, not bytes
#define configUSE_16_BIT_TICKS 0                               // uninteresting for 32 bit CPUs
#define configUSE_TIME_SLICING 1                               // To share time between tasks of the same priority
#define configIDLE_SHOULD_YIELD 1                              // Prevent Idle Task to starve other task @ priority 0

/* *********************** */
/* Synchronization Related */
/* *********************** */
#define configUSE_MUTEXES 0
#define configUSE_RECURSIVE_MUTEXES 0
#define configUSE_APPLICATION_TASK_TAG 0
#define configUSE_COUNTING_SEMAPHORES 0
#define configQUEUE_REGISTRY_SIZE 8
#define configUSE_QUEUE_SETS 0
#define configUSE_TASK_NOTIFICATIONS 1 // See Chapter 9
#define configTASK_NOTIFICATION_ARRAY_ENTRIES 3 // Notifications internal buffer size

/* ***** */
/* Tasks */
/* ***** */
#define configMAX_TASK_NAME_LEN 8 // Including trailing NULL. See Table 8 in book
#define configUSE_NEWLIB_REENTRANT 0
#define configENABLE_BACKWARD_COMPATIBILITY 0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5

/* System */
#define configSTACK_DEPTH_TYPE uint32_t
#define configMESSAGE_BUFFER_LENGTH_TYPE size_t

/* Memory allocation related definitions */
#define configSUPPORT_STATIC_ALLOCATION 1
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configTOTAL_HEAP_SIZE (128 * 1024)          // not used in heap_3.c (stdlib malloc/free)
#define configAPPLICATION_ALLOCATED_HEAP 0          // must be 1 if using heap_4.c/heap_5.c
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0 // if 1, this needs pvPortMallocStack() and vPortFreeStack() implementations

/* Hook function related definitions. */
#define configCHECK_FOR_STACK_OVERFLOW 0
#define configUSE_MALLOC_FAILED_HOOK 0
#define configUSE_SB_COMPLETED_CALLBACK 0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS 0
#define configUSE_TRACE_FACILITY 0
#define configUSE_STATS_FORMATTING_FUNCTIONS 0

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES 0
#define configMAX_CO_ROUTINE_PRIORITIES 1

/* Software timer related definitions. (System Daemon Task) */
#define configUSE_TIMERS 1
#define configUSE_DAEMON_TASK_STARTUP_HOOK 0 // If, must define a void vApplicationDaemonTaskStartupHook( void ); functiom
#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH 10
#define configTIMER_TASK_STACK_DEPTH configMINIMAL_STACK_SIZE

/* Interrupt nesting behaviour configuration. */
/*
#define configKERNEL_INTERRUPT_PRIORITY         [dependent of processor]
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    [dependent on processor and application]
#define configMAX_API_CALL_INTERRUPT_PRIORITY   [dependent on processor and application]
*/

/* SMP port only */
#define configNUM_CORES 1
#define configTICK_CORE 0
#define configRUN_MULTIPLE_PRIORITIES 0
#define configUSE_CORE_AFFINITY 0

/* ********************************** */
/* RP2040 SDK-FreeRTOS interoperation */
/* ********************************** */

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#define configSUPPORT_PICO_SYNC_INTEROP 1

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#define configSUPPORT_PICO_TIME_INTEROP 1

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#define configUSE_DYNAMIC_EXCEPTION_HANDLERS 0 // if 0 vPortSVCHandler(), xPortPendSVHandler() & xPortSysTickHandler() are automatically defined

/* Define to trap errors during development. */
#define configASSERT(x) 

/* Set the following definitions to 1 to include the API function, or zero
   to exclude the API function.
   Optional functions - most linkers will remove unused functions anyway
*/
#define INCLUDE_vTaskPrioritySet 0
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelete 0
#define INCLUDE_vTaskSuspend 0
#define INCLUDE_vTaskDelayUntil 0
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskGetSchedulerState 0
#define INCLUDE_xTaskGetCurrentTaskHandle 1
#define INCLUDE_uxTaskGetStackHighWaterMark 0
#define INCLUDE_xTaskGetIdleTaskHandle 0
#define INCLUDE_eTaskGetState 0
#define INCLUDE_xTimerPendFunctionCall 1
#define INCLUDE_xTaskAbortDelay 0
#define INCLUDE_xTaskGetHandle 0
#define INCLUDE_xTaskResumeFromISR 0
#define INCLUDE_xQueueGetMutexHolder 0

/* Sueltas */
/*
#define INCLUDE_xResumeFromISR           1
#define INCLUDE_xEventGroupSetBitFromISR 1
#define INCLUDE_xTaskGetHandle           0

*/

/* A header file that defines trace macro can be included here. */

#endif /* FREERTOS_CONFIG_H */