/*
   (c) Rafael González (astrorafael@gmail.com), LICA, Ftad. CC. Fisicas, UCM

   See project's LICENSE file.
*/

#pragma once        // Get rid of the old ifndef/define/endif __XX_H stuff

#ifdef __cplusplus
extern "C"
{
#endif

    /* ************************************************************************* */
    /*                         DATA TYPES AND DEFINITIONS                        */
    /* ************************************************************************* */

    typedef int (*console_cmd_exec_func_t)(int argc, char **argv);
    typedef void (*console_cmd_build_func_t)(size_t n, void** argtable);

    typedef struct
    {
        const char *name;                    // Command name (first word in the console)
        const char* help;                    // Brief text: what the command does 
        console_cmd_build_func_t build_func; // build arguments function (before argparse())
        console_cmd_exec_func_t exec_func;   // command execution function
        void** argtable;                     // Command line arguments specification, contents reset after every execution
        size_t N;                            // argtable array length
    } console_cmd_t;

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    void vConsoleRegister(console_cmd_t *command);

#ifdef __cplusplus
}
#endif




