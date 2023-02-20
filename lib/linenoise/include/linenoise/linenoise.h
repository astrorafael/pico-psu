/* ureadline.h
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LINENOISE_H
#define __LINENOISE_H

#include <stddef.h>
#include <stdbool.h>

#ifndef LINENOISE_MAX_LINE
#define LINENOISE_MAX_LINE 80       // for dynamic allocations
#endif

#ifndef LINENOISE_ALLOW_EMPTY
#define LINENOISE_ALLOW_EMPTY false // allow reading empty strings
#endif

#define LINENOISE_MALLOC_STANDARD 1 // use malloc()/calloc()/free()
#define LINENOISE_MALLOC_FREERTOS 2 // use pvPortMalloc()/pvPortCalloc()/pFree()

#ifdef __cplusplus
extern "C"
{
#endif
    /* serves to initialize the library, no VT100 probe */
    int  linenoiseProbe();

    char* linenoise(const char* prompt);
    void  linenoiseFree(void* ptr);

    /* the user prpvides the buffer, no need to free it */
    char *linenoiseStatic(const char* prompt, char* buffer, size_t buffer_length);

#ifdef __cplusplus
}
#endif

#endif /* __LINENOISE_H */
