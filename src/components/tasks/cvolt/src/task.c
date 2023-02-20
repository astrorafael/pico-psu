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

#include "hardware/pwm.h"
#include "pico/stdlib.h"

// ---------------------------
// Project specific components
// ---------------------------

#include "cvolt/utils.h"
#include "cvolt/task.h"
#include "cvolt/commands.h"

/* ************************************************************************* */
/*                      DEFINES AND ENUMERATIONS SECTION                     */
/* ************************************************************************* */

/* ************************************************************************* */
/*            PRIVATE DEFINITIONS AND DATATYPES SECTION                      */
/* ************************************************************************* */

static uint16_t initialVolt;
static uint16_t finalVolt;
static uint16_t stepVolt;
static uint16_t curVolt = CVOLT_CC_INITIAL;
;

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

extern TaskHandle_t xCVoltTask; // Global task identifier for the led task

/* ************************************************************************* */
/*                              HELPER FUNCIONS                              */
/* ************************************************************************* */

static void prvSetupHardware(void)
{
    gpio_set_function(CVOLT_PWM_OUT_PIN, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = GPIO_TO_PWM_SLICE(CVOLT_PWM_OUT_PIN);
    // Set period to (CVOLT_TOP_COUNT + 1) cycles
    pwm_set_wrap(slice_num, CVOLT_TOP_COUNT);
    // Set channel A output high for CVOLT_CC_INITIAL cycles before dropping
    pwm_set_chan_level(slice_num, GPIO_TO_PWM_CHANNEL(CVOLT_PWM_OUT_PIN), curVolt);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
}

static void prvUpdateCurrentVoltage(void)
{
    if (initialVolt <= finalVolt) // ramp up
    {
        curVolt = min(curVolt + stepVolt, finalVolt);
    }
    else if (curVolt - finalVolt < stepVolt) // ramp down, last step
    {
        curVolt = finalVolt;
    }
    else // ramp down
    {
        curVolt -= stepVolt;
    }
}
static void prvProcessNotification(TickType_t xTicksToDelay)
{
    uint32_t ulMessage;

    BaseType_t xReceived = xTaskNotifyWait(0x00, 0xffffffff, &ulMessage, xTicksToDelay);
    if (xReceived)
    {
        switch (CVOLT_CMD_DECODE_OPCODE(ulMessage))
        {
        case CVOLT_CMD_SET_VOLTAGE:
            curVolt = CVOLT_CMD_DECODE_VOLTAGE(ulMessage);
            pwm_set_chan_level(GPIO_TO_PWM_SLICE(CVOLT_PWM_OUT_PIN),
                               GPIO_TO_PWM_CHANNEL(CVOLT_PWM_OUT_PIN),
                               curVolt);
            break;

        case CVOLT_CMD_GET_VOLTAGE:
            printf("%d\n", curVolt);
            break;
        case CVOLT_CMD_FROM_VOLTAGE:
            initialVolt = CVOLT_CMD_DECODE_VOLTAGE(ulMessage);
            curVolt = initialVolt;
            break;
        case CVOLT_CMD_TO_VOLTAGE:
            finalVolt = CVOLT_CMD_DECODE_VOLTAGE(ulMessage);
            break;
        case CVOLT_CMD_STEP_VOLTAGE:
            stepVolt = CVOLT_CMD_DECODE_VOLTAGE(ulMessage);
            break;
        case CVOLT_CMD_NEXT:
            pwm_set_chan_level(GPIO_TO_PWM_SLICE(CVOLT_PWM_OUT_PIN),
                               GPIO_TO_PWM_CHANNEL(CVOLT_PWM_OUT_PIN),
                               curVolt);
            printf("%d\n", curVolt);
            prvUpdateCurrentVoltage();
            break;

        default:
            break;
        }
    }
}

/* ************************************************************************* */
/*                                 PUBLIC API                                */
/* ************************************************************************* */

void vCVoltTaskSetup(void)
{
    prvSetupHardware();
    vCVoltSetupCommands();
}

void vCVoltTask(void *pvParameters)
{
    while (true)
    {
        prvProcessNotification(portMAX_DELAY);
    }
}
