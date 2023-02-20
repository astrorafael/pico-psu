/*
   (c) Rafael González (astrorafael@gmail.com), LICA, Ftad. CC. Fisicas, UCM

   See project's LICENSE file.
*/

#pragma once

#include <FreeRTOS.h>
#include <task.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* ************************************************************************* */
    /*                         DATA TYPES AND DEFINITIONS                        */
    /* ************************************************************************* */

#ifndef GPIO_TO_PWM_SLICE
#define GPIO_TO_PWM_SLICE(gpio) (((gpio) >> 1U) & 0x07)
#endif

#ifndef GPIO_TO_PWM_CHANNEL
#define GPIO_TO_PWM_CHANNEL(gpio) ((gpio) & 0x1)
#endif

#define CVOLT_PWM_OUT_PIN 18 // GPIO 18 => PŴM output pin

#define CVOLT_TOP_COUNT  65534
#define CVOLT_CC_INITIAL (CVOLT_TOP_COUNT/2)

    /* ************************************************************************* */
    /*                               GLOBAL VARIABLES                            */
    /* ************************************************************************* */

    extern TaskHandle_t xCVoltTask; // Global task identifier for the led task

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    void vCVoltTaskSetup(void);          // Initializes task (hardware, commands, objects, etc)
    void vCVoltTask(void *pvParameters); // Infinite loop implementing the task

#ifdef __cplusplus
}
#endif
