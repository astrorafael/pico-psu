/*
   (c) Rafael González (astrorafael@gmail.com), LICA, Ftad. CC. Fisicas, UCM

   See project's LICENSE file.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    /* ************************************************************************* */
    /*                         DATA TYPES AND DEFINITIONS                        */
    /* ************************************************************************* */

#ifndef CONSOLE_PROMPT
#define CONSOLE_PROMPT "phot> "
#endif

#define COMMAND_LIST_SIZE 8 // maximun number of commands

    /* ************************************************************************* */
    /*                               GLOBAL VARIABLES                            */
    /* ************************************************************************* */

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    // This interface is for the main program

    void vConsoleTaskSetup();
    void vConsoleTask(void* pvParameters);

#ifdef __cplusplus
}
#endif