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

    /* Inter-task communication macros */

    /*
     * Commands: up to 256 allowed commands by using the
     * higher MS byte of a 32-bit word
     * Params are packed in the following 24 bit field
     * All commands are listed here even if they are not used in a given task variation
     */

    /*
        +---------+-----------------------+
        | 31...24 | 23 .................0 |
        +---------+-----------------------+
        | OPCODE  | ADDITIONAL PARAMETERS |
        +---------+-----------------------+
    */

#define CVOLT_CMD_DECODE_OPCODE(msg) (((msg)&0xFF000000))

/* COMMAND OPCODES */
#define CVOLT_CMD_SET_VOLTAGE (0x01 << 24)
#define CVOLT_CMD_GET_VOLTAGE (0x02 << 24)

#define CVOLT_CMD_LINSTEP_VOLTAGE (0x03 << 24)
#define CVOLT_CMD_NEXT (0x06 << 24)

/* SET VOLTAGE PARAMETERS */
// Voltage in 0...127 steps
#define CVOLT_CMD_ENCODE_VOLTAGE(value) ((value) & 0x0000007F)
#define CVOLT_CMD_DECODE_VOLTAGE(value) ((value) & 0x000007F)

#define CVOLT_CMD_ENCODE_FROM(from) (((from) << 16) & 0x007F0000)
#define CVOLT_CMD_ENCODE_TO(to) (((to) << 8) & 0x00007F00)
#define CVOLT_CMD_ENCODE_STEP(step) ((step) & 0x0000007F)

#define CVOLT_CMD_DECODE_FROM(value)  (((value) & 0x007F0000) >> 16)
#define CVOLT_CMD_DECODE_TO(value) (((value) & 0x00007F00) >> 8)
#define CVOLT_CMD_DECODE_STEP(value) (((value) & 0x0000007F))

    /* ************************************************************************* */
    /*                               API FUNCTIONS                               */
    /* ************************************************************************* */

    extern void vCVoltSetupCommands(void);

#ifdef __cplusplus
}
#endif
