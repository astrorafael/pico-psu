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
void *next_argtable[] = {
    NULL, // always help
    NULL  // always end
};

/* ************************************************************************* */
/*                           COMMAND IMPLEMENTATION                          */
/* ************************************************************************* */

void vCVNextCommandBuild(size_t n, void **argtable)
{
    argtable[0] = arg_lit0("h", "help", "print this help and exit");
    argtable[1] = arg_end(1);
    assert(arg_nullcheck(argtable) == 0);
}

int iCVNextCommandRun(int argc, char **argv)
{
    int exitcode = 0;
    uint32_t message = CVOLT_CMD_NEXT;
    xTaskNotify(xCVoltTask, message, eSetValueWithOverwrite);
    return exitcode;
}
