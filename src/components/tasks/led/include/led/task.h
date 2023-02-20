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
    /*                               GLOBAL VARIABLES                            */
    /* ************************************************************************* */

    extern TaskHandle_t xLEDTask; // Global task identifier for the led task

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    void vLEDTaskSetup(void);          // Initializes task (hardware, commands, objects, etc)
    void vLEDTask(void *pvParameters); // Infinite loop implementing the task

#ifdef __cplusplus
}
#endif
