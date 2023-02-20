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
#include "cvolt/commands/volt.h"
#include "cvolt/commands/linstep.h"
#include "cvolt/commands/next.h"

/* ************************************************************************* */
/*                      DEFINES AND ENUMERATIONS SECTION                     */
/* ************************************************************************* */

/* ************************************************************************* */
/*                               DATATYPES SECTION                           */
/* ************************************************************************* */

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

static console_cmd_t cvolt_cmd[3];

/* ************************************************************************* */
/*                           PUBLIC API FUNCTIONS                            */
/* ************************************************************************* */

void vCVoltSetupCommands(void)
{
    uint i = 0;

    cvolt_cmd[i].name = "volt";
    cvolt_cmd[i].help = "Get/Set a voltage level in arbitrary units";
    cvolt_cmd[i].build_func = vCVoltCommandBuild;
    cvolt_cmd[i].exec_func = iCVoltCommandRun;
    cvolt_cmd[i].argtable = cvolt_argtable;
    cvolt_cmd[i].N = sizeof(cvolt_argtable) / sizeof(cvolt_argtable[0]);
    vConsoleRegister(&cvolt_cmd[i]);
    ++i;

    cvolt_cmd[i].name = "linstep";
    cvolt_cmd[i].help = "Define a voltage linear stepping";
    cvolt_cmd[i].build_func = vCVLinStepCommandBuild;
    cvolt_cmd[i].exec_func = iCVLinStepCommandRun;
    cvolt_cmd[i].argtable = linstep_argtable;
    cvolt_cmd[i].N = sizeof(linstep_argtable) / sizeof(linstep_argtable[0]);
    vConsoleRegister(&cvolt_cmd[i]);
    ++i;

    cvolt_cmd[i].name = "next";
    cvolt_cmd[i].help = "Execute next step voltage";
    cvolt_cmd[i].build_func = vCVNextCommandBuild;
    cvolt_cmd[i].exec_func = iCVNextCommandRun;
    cvolt_cmd[i].argtable = next_argtable;
    cvolt_cmd[i].N = sizeof(next_argtable) / sizeof(next_argtable[0]);
    vConsoleRegister(&cvolt_cmd[i]);
    ++i;
}
