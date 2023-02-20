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
extern void *pvPortRealloc(void *pv, size_t size);

// -------------------
// C standard includes
// -------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ---------------------
// Third party libraries
// ---------------------

#include "pico/stdlib.h"

#include "linenoise/linenoise.h"
#include "argtable2/argtable2.h"

#include "cmc/cmc_list.h"
#include "cmc/ext_cmc_list.h"
#include "cmc/macro_defs.h"

// ---------------------------
// Project specific components
// ---------------------------

#include "console/console.h"
#include "console/task.h"

/* ************************************************************************* */
/*            PRIVATE DEFINITIONS AND DATATYPES SECTION                      */
/* ************************************************************************* */

#define CMDNAME "help"

// A PARAM is a standard way to pass required parameters to the lower level API.
// It is a tuple of form (PFX, SNAME, SIZE, K, V). In this case, not all of them
// are used, so we can leave them empty. We are creating a list of value int.
#define MY_PARAMS (cmdl, cmd_list, , , console_cmd_t *)

typedef struct cmd_list cmd_list_t;
typedef struct cmd_list_iter cmd_list_iter_t;

C_MACRO_COLLECTIONS_EXTENDED(CMC, LIST, MY_PARAMS, (ITER));

/* ************************************************************************* */
/*                          GLOBAL VARIABLES SECTION                         */
/* ************************************************************************* */

static struct CMC_ALLOC_NODE_NAME console_allocators = {pvPortMalloc, pvPortCalloc, pvPortRealloc, vPortFree};
static cmd_list_t *theCommandList;

TaskHandle_t xConsoleTask; // Global task identifier for the led task

// 'help' command arguments variable
static void *help_argtable[] = {
    NULL, // reserved for exceptional 'end' argument option
};

// 'help' command specification
static console_cmd_t help_cmd;

/* ************************************************************************* */
/*                              HELPER FUNCIONS                              */
/* ************************************************************************* */

static void vConsoleSplitLine(char *input, char ***argv, int *argc)
{
    char **vec = NULL;
    int N = 0;
    /* split string and append tokens to 'output' */
    char *p = strtok(input, " ");
    while (p != NULL)
    {
        N++;
        vec = pvPortRealloc(vec, sizeof(char *) * N);
        vec[N - 1] = p;
        p = strtok(NULL, " ");
    }
    *argc = N;
    *argv = vec;
}

// Forward declaration
static int iHelpCommandRun(int argc, char **argv);

static int iConsoleExecCommand(console_cmd_t *command, int argc, char **argv)
{
    void **argtable = command->argtable;
    size_t N = command->N;
    const char *name = command->name;
    console_cmd_exec_func_t exec_func = command->exec_func;
    console_cmd_build_func_t build_func = command->build_func;
    // Call the module build functionto initialize its argtable
    build_func(N, argtable);
    // always intercepts the help command, no matter what follows
    if (strcmp(argv[0], "help") == 0)
    {
        iHelpCommandRun(argc, argv);
        goto exit;
    }
    int nerrors = arg_parse(argc, argv, argtable);
    int exitcode = 0;

    /* help option in every command always takes precedence over parsing errors */
    struct arg_lit *help = argtable[0];
    if (help->count > 0)
    {
        printf("Usage: %s", name);
        arg_print_syntaxv(stdout, argtable, "\n");
        arg_print_glossary(stdout, argtable, "  %-10s %s\n");
        goto exit;
    }
    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0)
    {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout, argtable[N - 1], name);
        printf("Try '%s --help' for more information.\n", name);
        exitcode = -3;
        goto exit;
    }
    // finally execute the command
    exitcode = exec_func(argc, argv);
exit:
    /* deallocate each non-null entry in argtable */
    arg_freetable(argtable, N);
    return exitcode;
}

static void vConsoleExec(int argc, char **argv)
{
    bool found = false;
    for (
        cmd_list_iter_t iter = cmdl_iter_start(theCommandList);
        !cmdl_iter_at_end(&iter);
        cmdl_iter_next(&iter))
    {
        console_cmd_t *command = cmdl_iter_value(&iter);
        if (strcmp(command->name, argv[0]) == 0)
        {
            iConsoleExecCommand(command, argc, argv);
            found = true;
        }
    }
    if (!found)
    {
        printf("\t%s ???\n", argv[0]);
    }
}

static int vConsoleREPL(const char *prompt)
{
    int argc;
    char **argv;
    char *line;
    while (true)
    {
        while ((line = linenoise(prompt)) != NULL)
        {
            vConsoleSplitLine(line, &argv, &argc);
            vConsoleExec(argc, argv);
            vPortFree(argv);
            linenoiseFree(line);
        }
    }
    return 0; // really never gets here
}

static void vHelpCommandBuild(size_t n, void **argtable)
{
    argtable[0] = arg_end(1);
    assert(arg_nullcheck(argtable) == 0);
}

static int iHelpCommandRun(int argc, char **argv)
{
    cmd_list_iter_t iter = cmdl_iter_start(theCommandList);
    printf("Available commands (type <command>  [-h|--help] for details):\n");
    while (!cmdl_iter_at_end(&iter))
    {
        console_cmd_t *command = cmdl_iter_value(&iter);
        if (command->help)
        {
            printf("\t%-8s: %s.\n", command->name, command->help);
        }
        cmdl_iter_next(&iter);
    }
    return 0;
}

static void vHelpCommandSetup()
{
    help_cmd.name = CMDNAME;
    help_cmd.help = NULL;
    help_cmd.build_func = vHelpCommandBuild;
    help_cmd.exec_func = iHelpCommandRun;
    help_cmd.argtable = help_argtable;
    help_cmd.N = sizeof(help_argtable) / sizeof(help_argtable[0]);
    // Register to itself
    vConsoleRegister(&help_cmd);
}

/* ************************************************************************* */
/*                                 PUBLIC API                                */
/* ************************************************************************* */

void vConsoleRegister(console_cmd_t *cmd)
{
    int exitcode = cmdl_push_back(theCommandList, cmd);
    assert(exitcode != 0); // revisar esto
}

void vConsoleTask(void *pvParameters)
{
    vConsoleREPL(CONSOLE_PROMPT); // infinite loop REPL
    cmdl_free(theCommandList);
    vTaskDelete(NULL); // Kill itself if it ever goes here
}

void vConsoleTaskSetup()
{
    linenoiseProbe();
    theCommandList = cmdl_new_custom(COMMAND_LIST_SIZE, &(struct cmd_list_fval){NULL}, &console_allocators, NULL);
    assert(theCommandList != NULL);
    vHelpCommandSetup();
}
