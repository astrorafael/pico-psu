#include <FreeRTOS.h>
#include <memory.h>
#include "heap_ext.h"

void *pvPortRealloc(void *mem, size_t newsize)
{
    if (newsize == 0)
    {
        vPortFree(mem);
        return NULL;
    }
    void *p = pvPortMalloc(newsize);
    if (p && mem)
    {
        memcpy(p, mem, newsize);
        vPortFree(mem);
    }
    return p;
}
