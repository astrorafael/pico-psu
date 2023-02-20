/*
   (c) Rafael González (astrorafael@gmail.com), LICA, Ftad. CC. Fisicas, UCM

   See project's LICENSE file.
*/

/* ************************************************************************* */
/*                         INCLUDE HEADER SECTION                            */
/* ************************************************************************* */

// -----------------------
// FreeRTOS includes first
// -----------------------

#include <FreeRTOS.h>
#include <task.h>
extern void *pvPortRealloc(void *pv, size_t size); // Not defined in standard files

// -------------------
// C standard includes
// -------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ---------------------
// Third party libraries
// ---------------------

#include "pico/stdlib.h"

// ---------------------------
// Project specific components
// ---------------------------

#ifndef INCLUDE_CONSOLE_TASK
#define INCLUDE_CONSOLO_TASK 1
#endif

#ifndef INCLUDE_LED_TASK
#define INCLUDE_LED_TASK 1
#endif


#if INCLUDE_CONSOLE_TASK
#include "console/task.h"
#endif

#if INCLUDE_LED_TASK
#include "led/task.h"
#endif

#include "cvolt/task.h"


/* ************************************************************************* */
/*            PRIVATE DEFINITIONS AND DATATYPES SECTION                      */
/* ************************************************************************* */

#if INCLUDE_CONSOLE_TASK
#define CONSOLE_TASK_PRIOR 1
#define CONSOLE_TASK_NAME "CONSOLE" // 8 characters including trailing 0
#define CONSOLE_STACK_SIZE 512
#endif

#if INCLUDE_LED_TASK
#define LED_TASK_PRIOR 2
#define LED_TASK_NAME "LED"
#define LED_STACK_SIZE 128
#endif

#define CVOLT_TASK_PRIOR 3
#define CVOLT_TASK_NAME "CVOLT"
#define CVOLT_STACK_SIZE 384

/* ************************************************************************* */
/*                       PRIVATE  DATATYPES SECTION                          */
/* ************************************************************************* */

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

#if INCLUDE_CONSOLE_TASK
static StaticTask_t xConsoleTaskBuffer;
static StackType_t xConsoleStack[CONSOLE_STACK_SIZE];
#endif

#if INCLUDE_LED_TASK
TaskHandle_t xLEDTask;       // Global task identifier for the LED task
static StackType_t xLEDStack[LED_STACK_SIZE];
static StaticTask_t xLEDTaskBuffer;
#endif

TaskHandle_t xCVoltTask; // Global task identifier for the LED task
static StackType_t xCVoltStack[CVOLT_STACK_SIZE];
static StaticTask_t xCVoltTaskBuffer;

/* ************************************************************************* */
/*                              HELPER FUNCIONS                              */
/* ************************************************************************* */

static void prvSetup(void)
{
#if INCLUDE_CONSOLE_TASK
    vConsoleTaskSetup(); // console initialization first
#endif
#if INCLUDE_LED_TASK
    vLEDTaskSetup();
#endif
    vCVoltTaskSetup();
}

/* ************************************************************************* */
/*                                 PUBLIC API                                */
/* ************************************************************************* */

int main(void)
{
    /* Perform any hardware setup necessary. */
    stdio_init_all(); // we keep it here in case of using printf debug when setting up hardware
    prvSetup();


#if INCLUDE_LED_TASK
    xLEDTask = xTaskCreateStatic(
        vLEDTask,       // Task Function pointer
        LED_TASK_NAME,  // Task name, for debugging purposes only
        LED_STACK_SIZE, // Task stack size in words
        NULL,           // Task parameter
        LED_TASK_PRIOR, // Task priority
        xLEDStack,      // Task Stack
        &xLEDTaskBuffer // Task Control Block
    );
#endif

#if INCLUDE_CONSOLE_TASK
    xTaskCreateStatic(
        vConsoleTask,       // Task Function pointer
        CONSOLE_TASK_NAME,  // Task name, for debugging purposes only
        CONSOLE_STACK_SIZE, // Task stack size
        NULL,               // Task parameter
        CONSOLE_TASK_PRIOR, // Task priority
        xConsoleStack,      // Task Stack
        &xConsoleTaskBuffer // Task Control Block
    );
#endif

    xCVoltTask = xTaskCreateStatic(
        vCVoltTask,       // Task Function pointer
        CVOLT_TASK_NAME,  // Task name, for debugging purposes only
        CVOLT_STACK_SIZE, // Task stack size
        NULL,               // Task parameter
        CVOLT_TASK_PRIOR, // Task priority
        xCVoltStack,      // Task Stack
        &xCVoltTaskBuffer // Task Control Block
    );
    vTaskStartScheduler();
    for (;;); // should never reach here
}
