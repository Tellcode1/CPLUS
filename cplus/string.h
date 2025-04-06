#pragma once

#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "oop.h"

#define strval(instance) instance.value

object string {
    self(string);
    char *value;

    objectfn_pointer(string, len, u64)(selftype string);
    objectfn_pointer(string, set, void)(selftype string, char *value);
} string;

objectfn(string, len, u64)(string self) {
    u64 result = 0;
    while (true) {
        if (self.value[result] == '\0')
            return result;
        result++;
    }
}

objectfn(string, set, void)(string self, char *value) {
    self.value = (char*)malloc(strlen(value) + 1);
    if (self.value) 
        strcpy(self.value, value);
}

objectsetup(string)(string *result, char *value) {
    result->self = result;

    result->value = (char*)malloc(strlen(value) + 1);
    if (result->value) 
        strcpy(result->value, value);

    objectfn_setup(result, string, len);
    objectfn_setup(result, string, set);
}