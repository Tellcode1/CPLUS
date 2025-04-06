#pragma once

#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "oop.h"

#define strval(instance) instance.value

object string {
    self(string);
    char *value;

    objectfn_pointer(string, len, u64)(selftype string *self);
    objectfn_pointer(string, set, void)(selftype string *self, char *value);
    objectfn_pointer(string, count_char, u64)(selftype string *self, char ch);
} string;

objectfn(string, len, u64)(string *self) {
    u64 result = 0;
    while (true) {
        if (self->value[result] == '\0')
            return result;
        result++;
    }
}

objectfn(string, set, void)(string *self, char *value) {
    self->value = (char*)malloc(strlen(value) + 1);
    if (self->value) 
        strcpy(self->value, value);
}

objectfn(string, count_char, u64)(string *self, char ch) {
    u64 result = 0;

    for (u64 index = 0; index < self->len(self->self); index++) {
        if (self->value[index] == ch) {
            result++;
        }
    }

    return result;
}

objectsetup(string)(string *result, char *value) {
    result->self = result;

    result->value = (char*)malloc(strlen(value) + 1);
    if (result->value) 
        strcpy(result->value, value);

    objectfn_setup(result, string, len);
    objectfn_setup(result, string, set);
    objectfn_setup(result, string, count_char);
}
