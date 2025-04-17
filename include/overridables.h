#pragma once

/**
 * Including stdlib here isn't going to slow down compilation.
 * This is because stdlib will 99.9% be included in the files before here
 */
#include <stdlib.h>
#include <string.h>

/* calloc but takes in only one argument */
static inline void*
_unstupidify_calloc(size_t size)
{
    return calloc(1, size);
}

/**
 * If the user hasn't defined cplus_malloc to something else,
 * Possibly their own implementation,
 * We default to standard malloc.
 */
#ifndef cp_malloc
#  define cp_malloc malloc
#endif

/**
 * Standard calloc takes in two arguments.
 * For no reason at all. So we define it to a custom
 * function that parses the call to calloc.
 */
#ifndef cp_calloc
#  define cp_calloc _unstupidify_calloc
#endif

/**
 * Possibly wrap free around a function that
 * makes sure that the pointer provided is not NULL.
 */
#ifndef cp_free
#  define cp_free free
#endif

#ifndef cp_memcp
#  define cp_memcmp _cp_default_memcmp
#endif

#ifndef cp_mecpy
#  define cp_memcpy _cp_default_memcpy
#endif

#ifndef c_strdup
#  define cp_strdup _cp_default_strdup
#endif

void*
_cp_default_memcpy(void* dest, const void* src, size_t n)
{
    unsigned char*       d = (unsigned char*)dest;
    const unsigned char* s = (unsigned char*)src;
    while (n-- > 0) { *d++ = *s++; }
    return dest;
}

int
_cp_default_memcmp(const void* s1, const void* s2, size_t n)
{
    if ((s1 == NULL) || (s2 == NULL) || n == 0)
    {
        /* not equal / invalid input */
        return -1;
    }

    const unsigned char* a = (const unsigned char*)s1;
    const unsigned char* b = (const unsigned char*)s2;
    for (size_t i = 0; i < n; i++)
    {
        if (a[i] != b[i]) { return (int)(a[i] - b[i]); }
    }
    return 0;
}

char*
_cp_default_strdup(const char* src)
{
    if (src == NULL) { return NULL; }

    const size_t src_length = strlen(src);
    char*        new_string = (char*)cp_calloc(src_length + 1);
    strcpy(new_string, src);
    new_string[src_length] = '\0';
    return new_string;
}
