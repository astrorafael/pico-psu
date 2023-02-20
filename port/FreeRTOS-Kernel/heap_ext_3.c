#include <FreeRTOS.h>
#include <stdlib.h>

#include "task.h"
#include "heap_ext.h"

/* 
* Wrappers around NEWLIB calloc()/realloc() 
*/

void *pvPortCalloc(size_t nmemb, size_t size)
{
    void *pvReturn;
    vTaskSuspendAll();
    {
        pvReturn = calloc(nmemb, size);
    }
    xTaskResumeAll();
    return pvReturn;
}

void *pvPortRealloc(void *pv, size_t size)
{
    void *pvReturn;
    vTaskSuspendAll();
    {
        pvReturn = realloc(pv, size);
    }
    xTaskResumeAll();
    return pvReturn;
}
