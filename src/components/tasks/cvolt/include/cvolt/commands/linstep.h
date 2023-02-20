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

    extern void *linstep_argtable[5];

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    int iCVLinStepCommandRun(int argc, char **argv);
    void vCVLinStepCommandBuild(size_t n, void **argtable);

#ifdef __cplusplus
}
#endif