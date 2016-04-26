// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdlib.h>
#include <string.h>

#include "min_unit.h"
#include "str.h"

char *extra = "extra";

char *str_append_empty()
{
    char *empty = malloc(1);
    *empty = '\0';

    mu_assert(strlen(empty) == 0);

    char *result = str_append(&empty, extra);

    mu_assert(result != NULL);
    mu_assert(result != extra);
    mu_assert(result == empty);
    mu_assert(strcmp(result, extra) == 0);

    return 0;
}

void all_tests()
{
    mu_run_test(str_append_empty);
}

