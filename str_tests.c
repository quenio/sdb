// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

#include "min_unit.h"
#include "str.h"

#define MINIMUM_SIZE 16

char *str_append_empty()
{
    char *str = malloc(1);
    *str = '\0';

    mu_assert(strlen(str) == 0);
    mu_assert(malloc_size(str) == MINIMUM_SIZE);

    char *original = str;
    char *result = str_append(&str, "x");

    mu_assert(result != NULL);
    mu_assert(result == str);
    mu_assert(strcmp(result, "x") == 0);
    mu_assert(malloc_size(str) == MINIMUM_SIZE);
    mu_assert(original == str);

    return 0;
}

char *str_append_non_empty()
{
    char *str = malloc(2);
    str[0] = 'a';
    str[1] = '\0';

    mu_assert(strlen(str) == 1);
    mu_assert(malloc_size(str) == MINIMUM_SIZE);

    char *original = str;
    char *result = str_append(&str, "x");

    mu_assert(result != NULL);
    mu_assert(result == str);
    mu_assert(strcmp(result, "ax") == 0);
    mu_assert(malloc_size(str) == MINIMUM_SIZE);
    mu_assert(original == str);

    return 0;
}

char *str_append_beyond_minimum()
{
    // The string occupies the whole space allocated:
    size_t length = MINIMUM_SIZE-1;
    char *str = malloc(MINIMUM_SIZE);
    for (int i = 0; i < length; i++)
    {
        str[i] = 'a' + (char)i;
    }
    str[length] = '\0';

    // There's a subsequent block allocated in the heap:
    char *extra = malloc(1);
    printf("%s", extra);

    mu_assert(strlen(str) == length);
    mu_assert(malloc_size(str) == MINIMUM_SIZE);

    char *original = str;
    char *result = str_append(&str, "xx");

    mu_assert(result != NULL);
    mu_assert(result == str);
    mu_assert(strcmp(result, "abcdefghijklmnoxx") == 0);
    mu_assert(malloc_size(str) == 2 * MINIMUM_SIZE);
    mu_assert(original != str); // New allocation had to be relocated on the heap.

    return 0;
}

void all_tests()
{
    mu_test(str_append_empty);
    mu_test(str_append_non_empty);
    mu_test(str_append_beyond_minimum);
}

