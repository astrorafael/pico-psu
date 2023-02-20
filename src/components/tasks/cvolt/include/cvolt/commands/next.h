/*
   (c) Rafael González (astrorafael@gmail.com), LICA, Ftad. CC. Fisicas, UCM

   See project's LICENSE file.
*/

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* ************************************************************************* */
    /*                         DATA TYPES AND DEFINITIONS                        */
    /* ************************************************************************* */

    /* ************************************************************************* */
    /*                               GLOBAL VARIABLES                            */
    /* ************************************************************************* */

    extern void *next_argtable[2];

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    int iCVNextCommandRun(int argc, char **argv);
    void vCVNextCommandBuild(size_t n, void **argtable);

#ifdef __cplusplus
}
#endif