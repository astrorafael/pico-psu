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
#include "cvolt/commands.h"
#include "cvolt/utils.h"
#include "cvolt/task.h"

/* ************************************************************************* */
/*                      DEFINES AND ENUMERATIONS SECTION                     */
/* ************************************************************************* */

/* ************************************************************************* */
/*                               DATATYPES SECTION                           */
/* ************************************************************************* */

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

// 'volt' command arguments variable
void *cvolt_argtable[] = {
    NULL, // always help
    NULL, // set/get voltage
    NULL  // always end
};

/* ************************************************************************* */
/*                           COMMAND IMPLEMENTATION                          */
/* ************************************************************************* */

void vCVoltCommandBuild(size_t n, void **argtable)
{
    argtable[0] = arg_lit0("h", "help", "print this help and exit");
    argtable[1] = arg_int0("s", "set", "<value>", "value = [0...127]");
    argtable[2] = arg_end(1);
    assert(arg_nullcheck(argtable) == 0);
    struct arg_int *volt = argtable[1];
    volt->hdr.flag |= ARG_HASOPTVALUE;
    volt->ival[0] = CVOLT_CC_INITIAL;
}

int iCVoltCommandRun(int argc, char **argv)
{
    uint32_t opcode = 0;
    uint32_t payload = 0;
    uint32_t message;

    struct arg_int *volt = (struct arg_int *)cvolt_argtable[1];

    if (volt->count > 0)
    {
        uint v = clip(volt->ival[0], 0, 127);
        // finally execute the command, once we know that ist arguments have been parsed
        opcode = CVOLT_CMD_SET_VOLTAGE;
        payload |= CVOLT_CMD_ENCODE_VOLTAGE(v);
    }
    else
    {
        opcode = CVOLT_CMD_GET_VOLTAGE;
    }
    message = opcode | payload;
    if (message != 0)
    {
        xTaskNotify(xCVoltTask, message, eSetValueWithOverwrite);
    }
    return 0;
}
