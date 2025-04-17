#pragma once

#include "overridables.h"

#include "oop.h"
#include "types.h"
#include <string.h>

#define cp_strval(instance) instance.value

object cp_string
{
    self(cp_string);
    char* value;

    objectfn_pointer(cp_string, len, size_t)(selftype cp_string * self);
    objectfn_pointer(cp_string, set, void)(selftype cp_string * self, const char* value);
    objectfn_pointer(cp_string, count_char, size_t)(selftype cp_string * self, char ch);
}
cp_string;

objectfn(cp_string, len, size_t)(cp_string* self)
{
    size_t result = 0;
    while (self->value[result] != '\0') { result++; }
    return result;
}

objectfn(cp_string, set, void)(cp_string* self, const char* value) { self->value = cp_strdup(value); }

objectfn(cp_string, count_char, size_t)(cp_string* self, char ch)
{
    size_t result = 0;

    for (size_t index = 0; index < self->len(self->self); index++)
    {
        if (self->value[index] == ch) { result++; }
    }

    return result;
}

objectsetup(cp_string)(cp_string* result, const char* value)
{
    result->self  = result;
    result->value = cp_strdup(value);

    objectfn_setup(result, cp_string, len);
    objectfn_setup(result, cp_string, set);
    objectfn_setup(result, cp_string, count_char);

    return result;
}
