#pragma once

#ifdef	__cplusplus
extern "C"
{
#endif

// Allows redefinition for alternative Heap management

#define ARGTABLE2_STANDARD_MALLOC 1
#define ARGTABLE2_FREERTOS_MALLOC 2

#ifndef ARGTABLE2_MALLOC
#define ARGTABLE2_MALLOC ARGTABLE2_STANDARD_MALLOC
#endif

#if ARGTABLE2_MALLOC == ARGTABLE2_STANDARD_MALLOC
#include <stdlib.h>
#define argtable2_malloc  malloc
#define argtable2_calloc  calloc
#define argtable2_realloc realloc
#define argtable2_free    free
#elif ARGTABLE2_MALLOC == ARGTABLE2_FREERTOS_MALLOC
#include <FreeRTOS.h>
extern void *pvPortRealloc(void *pv, size_t size);
#define argtable2_malloc  pvPortMalloc
#define argtable2_calloc  pvPortCalloc
#define argtable2_realloc pvPortRealloc
#define argtable2_free    vPortFree
#else
#error "ARGTABLE2_MALLOC allowed values are 1 for 'standard malloc()' or 2 for FreeRTOS"
#endif


#ifdef	__cplusplus
}
#endif
