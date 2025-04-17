#include "include/string.h"
#include <stdio.h>
#include <string.h>

int
main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    const char*      test_c_string = "Hello, world!";
    cp_string string init(cp_string)(&string, strdup(test_c_string));

    size_t len = string.len(string.self);
    printf("Length: %zu | Expected: %zu\n", len, strlen(test_c_string));

    char   ch    = 'l';
    size_t count = string.count_char(string.self, ch);
    printf("Count of '%c' in \"%s\": %zu\n", ch, strval(string), count);

    const char* new_test_c_string = "Goodbye world.";
    string.set(string.self, strdup(new_test_c_string));
    printf("New string: %s\n", string.value);

    len = string.len(string.self);
    printf("New Length: %zu | Expected : %zu\n", len, strlen(new_test_c_string));

    count = string.count_char(string.self, 'o');
    printf("Count of 'o' in \"%s\": %zu\n", new_test_c_string, count);

    return 0;
}
