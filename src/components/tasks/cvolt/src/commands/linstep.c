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

// 'linstep' command arguments variable
void *linstep_argtable[] = {
    NULL, // always help
    NULL, // from voltage
    NULL, // to voltage
    NULL, // step voltage
    NULL  // always end
};

/* ************************************************************************* */
/*                           COMMAND IMPLEMENTATION                          */
/* ************************************************************************* */

void vCVLinStepCommandBuild(size_t n, void **argtable)
{
    argtable[0] = arg_lit0("h", "help", "print this help and exit");
    argtable[1] = arg_int1("f", "from", "<value>", "value = [0...65535]");
    argtable[2] = arg_int1("t", "to", "<value>", "value = [0...65535]");
    argtable[3] = arg_int1("s", "step", "<value>", "value = [0...65535]");
    argtable[4] = arg_end(1);
    assert(arg_nullcheck(argtable) == 0);
}

int iCVLinStepCommandRun(int argc, char **argv)
{
    int exitcode = 0;
    uint32_t message;

    struct arg_int *from = (struct arg_int *)linstep_argtable[1];
    message = CVOLT_CMD_FROM_VOLTAGE | CVOLT_CMD_ENCODE_VOLTAGE(from->ival[0]);
    xTaskNotify(xCVoltTask, message, eSetValueWithOverwrite);

    struct arg_int *to = (struct arg_int *)linstep_argtable[2];
    message = CVOLT_CMD_TO_VOLTAGE | CVOLT_CMD_ENCODE_VOLTAGE(to->ival[0]);
    xTaskNotify(xCVoltTask, message, eSetValueWithOverwrite);

    struct arg_int *step = (struct arg_int *)linstep_argtable[3];
    message = CVOLT_CMD_STEP_VOLTAGE | CVOLT_CMD_ENCODE_VOLTAGE(step->ival[0]);
    xTaskNotify(xCVoltTask, message, eSetValueWithOverwrite);

    return exitcode;
}
