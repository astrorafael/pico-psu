#include <unistd.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/time.h>
#include <unistd.h>

#include "linenoise.h"

// Allows redefinition for alternative Heap management

#ifndef LINENOISE_MALLOC
#define LINENOISE_MALLOC LINENOISE_MALLOC_STANDARD
#endif

#if LINENOISE_MALLOC == LINENOISE_MALLOC_STANDARD
#include <stdlib.h>
#define linenoise_xmalloc  malloc
#define linenoise_xcalloc  calloc
#define linenoise_xrealloc realloc
#define linenoise_xfree    free
#elif LINENOISE_MALLOC == LINENOISE_MALLOC_FREERTOS
#include <FreeRTOS.h>
#define linenoise_xmalloc pvPortMalloc
#define linenoise_xcalloc pvPortCalloc
#define linenoise_xrealloc pvPortRealloc
#define linenoise_xfree vPortFree
#else
#error "LINENOISE_MALLOC alowed values are 1 for 'standard malloc()' or 2 for FreeRTOS"
#endif

enum KEY_ACTION
{
    KEY_NULL = 0,   /* NULL */
    CTRL_A = 1,     /* Ctrl+a */
    CTRL_B = 2,     /* Ctrl-b */
    CTRL_C = 3,     /* Ctrl-c */
    CTRL_D = 4,     /* Ctrl-d */
    CTRL_E = 5,     /* Ctrl-e */
    CTRL_F = 6,     /* Ctrl-f */
    CTRL_H = 8,     /* Ctrl-h */
    TAB    = 9,     /* Tab */
    LF     = 10,    /* Line Feed */
    CTRL_K = 11,    /* Ctrl+k */
    CTRL_L = 12,    /* Ctrl+l */
    CR    = 13,     /* Carriage Return, aka, 'Enter' */
    CTRL_N = 14,    /* Ctrl-n */
    CTRL_P = 16,    /* Ctrl-p */
    CTRL_T = 20,    /* Ctrl-t */
    CTRL_U = 21,    /* Ctrl+u */
    CTRL_W = 23,    /* Ctrl+w */
    ESC = 27,       /* Escape */
    BACKSPACE = 127 /* Backspace */
};

static void flushWrite(void)
{
    if (__fbufsize(stdout) > 0) {
        fflush(stdout);
    }
}

static void sanitize(char *src)
{
    char *dst = src;
    for (int c = *src++; c != 0; c = *src++) {
        if (isprint(c)) {
            *dst++ = c;
        }
    }
    *dst = 0;
}

static size_t linenoiseDumb(char *buf, size_t buflen, const char *prompt)
{
    /* dumb terminal, fall back to fgets */
    fputs(prompt, stdout);
    size_t count = 0;
    while (count < buflen) {
        int c = fgetc(stdin);
        if (c == CR) {
            break;
        }
        else if (c >= 0x1c && c <= 0x1f) {
            continue; /* consume arrow keys */
        }
        else if (c == BACKSPACE || c == 0x8) {
            if (count > 0) {
                buf[count - 1] = 0;
                count--;
            }
            fputs("\x08 ", stdout); /* Windows CMD: erase symbol under cursor */
        } else {
            buf[count++] = c;
        }
        fputc(c, stdout); /* echo */
    }
    fputc('\n', stdout);
    flushWrite();
    return count;
}

/* This is just a wrapper the user may want to call in order to make sure
 * the linenoise returned buffer is freed with the same allocator it was
 * created with .Useful when the main program is using an alternative
 * allocator.
 */
void linenoiseFree(void *ptr)
{
    linenoise_xfree(ptr);
}

int linenoiseProbe()
{
    setvbuf(stdin, NULL, _IONBF, 0); // Disable buffering on stdin
    return 0;
}

char* linenoise(const char* prompt)
{
    char* buffer = linenoise_xcalloc(1, (LINENOISE_MAX_LINE)+1);
    if (buffer == NULL) {
        return NULL;
    }
    size_t count = linenoiseDumb(buffer, LINENOISE_MAX_LINE, prompt);
    if (count > 0) {
        sanitize(buffer);
        count = strlen(buffer);
    } else if (count == 0 && ! LINENOISE_ALLOW_EMPTY) {
        linenoise_xfree(buffer);
        return NULL;
    }
    return buffer;
}


char* linenoiseStatic(const char* prompt, char* buffer, size_t buffer_length)
{
    size_t count = linenoiseDumb(buffer, buffer_length, prompt);
    if (count > 0) {
        sanitize(buffer);
        count = strlen(buffer);
    }  else if (count == 0 && ! LINENOISE_ALLOW_EMPTY) {
        return NULL;
    }
    return buffer;
}