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

#define LED_CMD_DECODE_OPCODE(msg) (((msg)&0xFF000000))

/* COMMAND OPCODES */
#define LED_CMD_SET_MODE (0x01 << 24)
#define LED_CMD_GET_MODE (0x02 << 24)

/* SET VOLTAGE PARAMETERS */
// Mode 0, off, 1, on, 2 toggle
#define LED_CMD_ENCODE_MODE(value) ((value)&0x00000003)
#define LED_CMD_DECODE_MODE(value) ((value)&0x00000003)

        /* ************************************************************************* */
        /*                               API FUNCTIONS                               */
        /* ************************************************************************* */

        extern void vLEDSetupCommands();

#ifdef __cplusplus
}
#endif
