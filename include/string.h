#pragma once

#include "overridables.h"

#include "types.h"
#include "oop.h"

#define strval(instance) instance.value

object cp_string
{
    self(cp_string);
    char* value;

    objectfn_pointer(cp_string, len, size_t)(selftype cp_string * self);
    objectfn_pointer(cp_string, set, void)(selftype cp_string * self, char* value);
    objectfn_pointer(cp_string, count_char, size_t)(selftype cp_string * self, char ch);
}
cp_string;

objectfn(cp_string, len, size_t)(cp_string* self)
{
    size_t result = 0;
    while (true)
    {
        if (self->value[result] == '\0') return result;
        result++;
    }
}

objectfn(cp_string, set, void)(cp_string* self, char* value)
{
    size_t length = 0;
    while (true)
    {
        if (self->value[length] == '\0') break;
        length++;
    }

    self->value = (char*)cp_calloc(length + 1);
    if (self->value != NULL)
    {
        size_t length = 0;
        while (true)
        {
            self->value[length] = value[length];
            if (value[length] == '\0') break;
            length++;
        }
    }
}

objectfn(cp_string, count_char, size_t)(cp_string* self, char ch)
{
    size_t result = 0;

    for (size_t index = 0; index < self->len(self->self); index++)
    {
        if (self->value[index] == ch) { result++; }
    }

    return result;
}

objectsetup(cp_string)(cp_string* result, char* value)
{
    result->self = result;

    size_t length = 0;
    while (true)
    {
        if (value[length] == '\0') break;
        length++;
    }

    result->value = (char*)cp_calloc(length + 1);
    if (result->value != NULL)
    {
        size_t length2 = 0;
        while (true)
        {
            result->value[length2] = value[length2];
            if (value[length2] == '\0') break;
            length2++;
        }
    }

    objectfn_setup(result, cp_string, len);
    objectfn_setup(result, cp_string, set);
    objectfn_setup(result, cp_string, count_char);

    return result;
}
