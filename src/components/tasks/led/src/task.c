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

// -------------------
// C standard includes
// -------------------

#include <stdio.h>

// ---------------------
// Third party libraries
// ---------------------

#include "pico/stdlib.h"

// ---------------------------
// Project specific components
// ---------------------------

#include "led/task.h"

#if INCLUDE_LED_CMD
#include "led/command.h"
#endif

/* ************************************************************************* */
/*                      DEFINES AND ENUMERATIONS SECTION                     */
/* ************************************************************************* */

/* ************************************************************************* */
/*            PRIVATE DEFINITIONS AND DATATYPES SECTION                      */
/* ************************************************************************* */

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

extern TaskHandle_t xLEDTask;                // Global task identifier for the led task
static const uint uiLEDPin = PICO_DEFAULT_LED_PIN; //  LED Pin identifier

/* ************************************************************************* */
/*                              HELPER FUNCIONS                              */
/* ************************************************************************* */

static void prvSetupHardware(uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

#if INCLUDE_LED_CMD

static void prvLEDProcessNotification(TickType_t xTicksToDelay)
{
    uint32_t ulMessage;
    static BaseType_t xMode = 2;
    extern const uint uiLEDPin;

    BaseType_t xReceived = xTaskNotifyWait(0x00, 0xffffffff, &ulMessage, xTicksToDelay);
    if (xReceived)
    {
        switch (LED_CMD_DECODE_OPCODE(ulMessage))
        {
        case LED_CMD_SET_MODE:
            xMode = LED_CMD_DECODE_MODE(ulMessage);
            if (xMode < 2)
                gpio_put(uiLEDPin, xMode);
            break;
        case LED_CMD_GET_MODE:
            if (xMode == 0)
                puts("off");
            else if (xMode == 1)
                puts("on");
            else
                puts("blink");
            break;
        default:
            break;
        }
    }
    if (xMode == 2)
    {
        gpio_xor_mask(1 << uiLEDPin);
    }
}
#else
static inline void vLEDSetupCommands)(void)
{
}
#endif

/* ************************************************************************* */
/*                                 PUBLIC API                                */
/* ************************************************************************* */

void vLEDTaskSetup(void)
{
    prvSetupHardware(uiLEDPin);
    vLEDSetupCommands();
}

#if INCLUDE_LED_CMD

void vLEDTask(void *pvParameters)
{
    while (true)
    {
        prvLEDProcessNotification(pdMS_TO_TICKS(1000));
    }
}

#else

void vLEDTask(void *pvParameters)
{
    extern uint uiLEDPin;
    extern TickType_t xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();
    while (true)
    {
        gpio_xor_mask(1 << uiLEDPin);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}
#endif
