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
#include <string.h>

// ---------------------
// Third party libraries
// ---------------------

#include "argtable2/argtable2.h"

// ---------------------------
// Project specific components
// ---------------------------

#include "console/console.h"
#include "led/command.h"

/* ************************************************************************* */
/*                      DEFINES AND ENUMERATIONS SECTION                     */
/* ************************************************************************* */

#define CMDNAME "led"

/* ************************************************************************* */
/*                               DATATYPES SECTION                           */
/* ************************************************************************* */

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

// 'led' command arguments variable
static void *led_argtable[] = {
    NULL, // always help
    NULL, // an action
    NULL  // always end
};

// 'led' command specification
static console_cmd_t led_cmd;

extern TaskHandle_t xLEDTask;


/* ************************************************************************* */
/*                     COMMAND IMPLEMENTATION SECTION                        */
/* ************************************************************************* */

// forward declaration
static int iLEDCommandRun(int argc, char **argv);
static void vLEDCommandBuild(size_t n, void **argtable);

void vLEDSetupCommands()
{
    led_cmd.name = CMDNAME;
    led_cmd.help = "Get/Set the on/off/blink state of on-board LED";
    led_cmd.build_func = vLEDCommandBuild;
    led_cmd.exec_func = iLEDCommandRun;
    led_cmd.argtable = led_argtable;
    led_cmd.N = sizeof(led_argtable) / sizeof(led_argtable[0]);
    // Register to console
    vConsoleRegister(&led_cmd);
}

static void vLEDCommandBuild(size_t n, void **argtable)
{
    argtable[0] = arg_lit0("h", "help", "print this help and exit");
    argtable[1] = arg_str0("s", "state", "<value>", "value = [on|off|blink]");
    argtable[2] = arg_end(4);
    assert(arg_nullcheck(argtable) == 0);
    struct arg_str *led = argtable[1];
    led->hdr.flag |= ARG_HASOPTVALUE;
    led->sval[0] = "blink";
}

static int iLEDCommandRun(int argc, char **argv)
{
    int exitcode = 0;
    uint32_t opcode = 0;
    uint32_t payload = 0;
    uint32_t message;

    // finally execute the command, once we know that ist arguments have been parsed
    struct arg_str *led = (struct arg_str *)led_argtable[1];

    if (led->count > 0)
    {
        opcode = LED_CMD_SET_MODE;
        if (strcmp(led->sval[0], "on") == 0)
        {
            payload |= LED_CMD_ENCODE_MODE(1);
        }
        else if (strcmp(led->sval[0], "off") == 0)
        {
            payload |= LED_CMD_ENCODE_MODE(0);
        }
        else if (strcmp(led->sval[0], "blink") == 0)
        {
            payload |= LED_CMD_ENCODE_MODE(2);
        }
    }
    else
    {
        opcode = LED_CMD_GET_MODE;
    }
    message = opcode | payload;
    if (message != 0)
    {
        xTaskNotify(xLEDTask, message, eSetValueWithOverwrite);
    }
    return exitcode;
}
